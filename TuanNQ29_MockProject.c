#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "srec.h"

int main()
{
    FILE *file_input; /* File input */
    FILE *file_output; /* File output */
    char buff[SREC_SIZE]; /* Bộ đệm dùng để lưu giá trị dòng đang đọc */
    char s0Address[4]; /* Mảng lưu giá trị địa chỉ của bản ghi S0 */
    bool isS0Exist = false; /* Biến logic kiểm tra bản ghi S0 đã tồn tại hay không */
    bool *isS0Exist_p = &isS0Exist; /* Con trỏ trỏ đến biến kiểm tra bản ghi S0 đã tồn tại hay không */
    bool isLineError = false; /* Biến logic kiểm tra dòng đang đọc có bị lỗi hay không */
    bool *isLineError_p = &isLineError; /* Con trỏ trỏ đến biến logic kiểm tra dòng đang đọc có bị lỗi hay không */
    bool isFileError = false; /* Biến logic kiểm tra file có bị lỗi hay không */
    bool *isFileError_p = &isFileError; /* Con trỏ trỏ đến biến logic kiểm tra file có bị lỗi hay không */
    bool fileEnd = false; /*Biến logic kiểm tra kết thúc file*/
    int listError[20]; /* Mảng lưu danh sách lỗi của dòng đang đọc */
    int countError = -1; /* Biến lưu số lỗi của dòng đang đọc */
    int *countError_p = &countError; /* Con trỏ trỏ đến biến lưu số lỗi của dòng đang đọc */
    int lineNumber = 1; /* Biến lưu số hiệu dòng của file */
    int *lineNumber_p = &lineNumber; /* Con trỏ trỏ đến biến lưu số hiệu dòng của file */
    int style = 0; /* Biến kiểm tra style S19, S28, S37 của file */
    int *style_p = &style; /* Con trỏ trỏ đến biến kiểm tra style S19, S28, S37 của file */
    int terminate = 0; /* Biến kiểm tra file có bản ghi kết thúc S7, S8 hoặc S9 hay không */
    int *terminate_p = &terminate; /* Con trỏ trỏ đến biến kiểm tra terminate của file */

    /* Mở và đọc file Srecord */
    file_input = fopen(SRECORD_INPUT, "r"); 

    /* Nếu file tồn tại thì tiến hành phân tích cú pháp file và thông báo lỗi nếu có. 
    Nếu file không có lỗi thì in giá trị address và data ra file Output.txt */
    if (file_input != NULL)
    {
        /* Kiểm tra điều kiện kết thúc file */
        while (!feof(file_input))
        {
            fgets(buff, SREC_SIZE, (FILE*)file_input); /* Đọc giá trị từng dòng vào mảng buff với SREC_SIZE phần tử */

            /* Trường hợp dòng cuối cùng của file không có phần tử nào thì lập tức thoát ra khỏi vòng lặp.
            Trường hợp này khác với trường hợp newline rỗng xuất hiện trong file, do newline rỗng vẫn có
            một phần tử là ký tự xuống dòng */
            if (strlen(buff) == 0)
            {
                fileEnd = true; /* Đánh dấu kết thúc file vào biến */
                break;
            }

            if (buff[1] == SREC_TYPE_S0) /* Kiểm tra trường type có phải S0 hay không */
            {
                /* Cắt 4 ký tự tại vị trí address đưa vào mảng s0Address */
                strncpy(s0Address, buff+4, 4);

                /* Kiểm tra giá trị header, có thể xảy ra lỗi S0 đã tồn tại và địa chỉ của S0 khác 0000 */
                SREC_Check_S0(isS0Exist_p, listError, s0Address, isLineError_p, isFileError_p, countError_p);
            }
            
            /* Kiểm tra lỗi dòng mới bị rỗng */
            if (!SREC_CheckNewlineError(buff, listError, isLineError_p, isFileError_p, countError_p))
            {
                /* Kiểm tra sự tồn tại S0, nếu S0 không tồn tại thì lập tức kết thúc việc đọc file 
                và in ra lỗi (lỗi ảnh hưởng đến phần file phía sau) */
                if (!SREC_Check_S0_Exist(isS0Exist_p, listError, isLineError_p, isFileError_p, countError_p))
                {
                    SREC_PrintError(buff, listError, lineNumber_p, countError_p);
                    break;
                }

                /* Kiểm tra định dạng dòng hiện tại, có thể xảy ra lỗi ký tự đầu tiên khác S và ký tự
                type không thuộc đoạn từ 0 đến 9 */
                SREC_CheckFormat(buff, listError, isLineError_p, isFileError_p,countError_p);

                /* Kiểm tra các ký tự được đọc có phải ký tự hexa hay không, nếu đúng là ký tự hexa thì 
                thực hiện tiếp các công việc kiểm tra style, byte count, checksum, độ dài bản ghi */
                if (SREC_CheckHexaValue(buff, listError, isLineError_p, isFileError_p, countError_p))
                {
                    if (buff[1] != SREC_TYPE_S0)
                    {
                        /* Kiểm tra style, nếu style không đúng thì lập tức kết thúc việc đọc file 
                        và in ra lỗi (lỗi ảnh hưởng đến phần file phía sau) */
                        if (!SREC_CheckStyle(buff, style_p, terminate_p, listError, isLineError_p, isFileError_p, countError_p))
                        {
                            SREC_PrintError(buff, listError, lineNumber_p, countError_p);
                            break;
                        }
                    }

                    /* Kiểm tra terminate của file, nếu đã xuất hiện terminate thì kết thúc việc đọc file
                    và in ra lỗi (lỗi ảnh hưởng đến phần file phía sau) */
                    if (SREC_CheckTerminate(buff, style_p, terminate_p, listError, isLineError_p, isFileError_p, countError_p))
                    {
                        SREC_PrintError(buff, listError, lineNumber_p, countError_p);
                        break;
                    }

                    /* Kiểm tra byte count */
                    SREC_CheckByteCount(buff, listError, isLineError_p, isFileError_p, countError_p);

                    /* Kiểm tra checksum */
                    SREC_CheckChecksum(buff, listError, isLineError_p, isFileError_p, countError_p);

                    /* Kiểm tra độ dài bản ghi hiện tại */
                    SREC_CheckLength(buff, listError, isLineError_p, isFileError_p, countError_p);
                }
            }

            /* Nếu xuất hiện lỗi thì in ra màn hình lỗi */
            if (isLineError == true)
            {
                SREC_PrintError(buff, listError, lineNumber_p, countError_p);
            }

            /* Reset biến kiểm tra dòng có bị lỗi hay không và bộ đếm số lỗi trên dòng */
            isLineError = false;
            countError = -1;
            /* Reset phần tử của mảng bộ đệm về null */
            memset(buff, '\0', SREC_SIZE * sizeof(char));

            lineNumber++; /* Tăng bộ đếm số dòng */
        }

        fclose(file_input); /* Đóng file input, kết thúc quá trình parse file */

        /* Kiểm tra đã đọc hết file hay chưa và file có tồn tại bản ghi terminate không */
        if (terminate != 2 && fileEnd == true)
        {
            isFileError = true;
            printf("\nNot found terminate record!\n");
        }
        /* Nếu quá trình parse file xác nhận file không bị lỗi thì xuất address và data ra file output */
        /* Để giảm bộ nhớ phải sử dụng do cần tạo mảng nhiều chiều để lưu giá trị address và data trên 
        mỗi dòng được đọc, việc đọc file input sẽ được thực hiện 2 lần: lần 1 để kiểm tra lỗi và lần 2
        để ghi ra file output. Như vậy sau khi kiểm tra file không có lỗi, chỉ cần sử dụng 2 biến để lưu
        giá trị address và data trên mỗi dòng và truyền vào file output. Mặc dù vậy tốc độ thực hiện 
        chương trình sẽ bị giảm */
        else if (isFileError == false)
        {
            printf("\nParse file SUCCESS. Writing to output file ...\n");
            file_output = fopen(SRECORD_OUTPUT, "w"); /* Mở file output ở chế độ ghi */
            file_input = fopen(SRECORD_INPUT, "r"); /* Mở file input ở chế độ đọc */
            WritingToOutputFile(file_input, file_output, buff); /* Thực hiện ghi giá trị từ file input vào file output */
            fclose(file_input); /* Đóng file input */
            fclose(file_output); /* Đóng file output, kết thúc quá trình ghi */
            sleep(1); // Trễ 1s
            printf("--> SUCCESSFUL");
        }
    }
    else
    {
        printf("\nFile not found!\n"); /* In ra màn hình lỗi không tìm thấy file */
    }

    return 0;
}