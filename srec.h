#ifndef SREC_H
#define SREC_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SRECORD_INPUT "Uart_HelloWorld.srec" /* Tên tệp đầu vào */
#define SRECORD_OUTPUT "Output.txt" /* Tên tệp đầu ra */

#define SREC_TYPE_S0 '0' /* Bản ghi loại S0 */
#define SREC_TYPE_S1 '1' /* Bản ghi loại S1 */
#define SREC_TYPE_S2 '2' /* Bản ghi loại S2 */
#define SREC_TYPE_S3 '3' /* Bản ghi loại S3 */
#define SREC_TYPE_S4 '4' /* Bản ghi loại S4 */
#define SREC_TYPE_S5 '5' /* Bản ghi loại S5 */
#define SREC_TYPE_S6 '6' /* Bản ghi loại S6 */
#define SREC_TYPE_S7 '7' /* Bản ghi loại S7 */ 
#define SREC_TYPE_S8 '8' /* Bản ghi loại S8 */ 
#define SREC_TYPE_S9 '9' /* Bản ghi loại S9 */

#define SREC_STYLE_S19 1 /* S19 Style - bản ghi 16 bit địa chỉ */
#define SREC_STYLE_S28 2 /* S28 Style - bản ghi 24 bit địa chỉ */
#define SREC_STYLE_S37 3 /* S37 Style - bản ghi 32 bit địa chỉ */

#define SREC_SIZE 514 /* Kích thước tối đa bản ghi */
#define SREC_START 'S' /* Kí tự bắt đầu bản ghi */
#define SREC_TYPE_LENGTH 1 /* Độ dài trường type (số ký tự hexa) */
#define SREC_BYTE_COUNT_LENGTH 2 /* Độ dài trường byte count (số ký tự hexa) */
#define SREC_ADDRESS_16_BIT 4 /* Độ dài trường address 16 bit (số ký tự hexa) */
#define SREC_ADDRESS_24_BIT 6 /* Độ dài trường address 24 bit (số ký tự hexa) */
#define SREC_ADDRESS_32_BIT 8 /* Độ dài trường address 32 bit (số ký tự hexa) */
#define SREC_DATA_LENGTH_MAX 64 /* Độ dài trường data tối đa (số ký tự hexa) */
#define SREC_CHECKSUM_LENGTH 2 /* Độ dài trường checksum (số ký tự hexa) */

/* Giới hạn */
#define SREC_S0_LENGTH_MIN 10 /* Độ dài tối thiểu bản ghi loại S0 (số ký tự hexa) */
#define SREC_S1_LENGTH_MIN 10 /* Độ dài tối thiểu bản ghi loại S1 (số ký tự hexa) */
#define SREC_S2_LENGTH_MIN 12 /* Độ dài tối thiểu bản ghi loại S2 (số ký tự hexa) */
#define SREC_S3_LENGTH_MIN 14 /* Độ dài tối thiểu bản ghi loại S3 (số ký tự hexa) */
#define SREC_S5_LENGTH 10 /* Độ dài cố định bản ghi loại S5 (số ký tự hexa) */
#define SREC_S6_LENGTH 12 /* Độ dài cố định bản ghi loại S6 (số ký tự hexa) */
#define SREC_S7_LENGTH 14 /* Độ dài cố định bản ghi loại S7 (số ký tự hexa) */
#define SREC_S8_LENGTH 12 /* Độ dài cố định bản ghi loại S8 (số ký tự hexa) */
#define SREC_S9_LENGTH 10 /* Độ dài cố định bản ghi loại S9 (số ký tự hexa) */
#define SREC_S0_LENGTH_MAX 74 /* Độ dài tối đa bản ghi loại S0 (số ký tự hexa) */
#define SREC_S1_LENGTH_MAX 74 /* Độ dài tối đa bản ghi loại S1 (số ký tự hexa) */
#define SREC_S2_LENGTH_MAX 76 /* Độ dài tối đa bản ghi loại S2 (số ký tự hexa) */
#define SREC_S3_LENGTH_MAX 78 /* Độ dài tối đa bản ghi loại S3 (số ký tự hexa) */

#define SREC_CORRECT 0 /* File không lỗi */
#define SREC_ERROR_FORMAT -1 /* Lỗi định dạng, bao gồm sai trường S và Type */
#define SREC_ERROR_CHECKSUM -2 /* Lỗi checksum không chính xác */
#define SREC_ERROR_NEWLINE -3 /* Lỗi dòng mới bị rỗng */
#define SREC_ERROR_MULTI_S0 -4 /* Lỗi xuất hiện nhiều S0 trong file */
#define SREC_ERROR_S0_ADDRESS -5 /* Lỗi địa chỉ S0 khác địa chỉ 0000 */
#define SREC_ERROR_BYTE_COUNT -6 /* Lỗi byte count không chính xác */
#define SREC_ERROR_S0_NOT_EXIST -7 /* Lỗi không tồn tại S0 */
#define SREC_ERROR_STYLE -8 /* Lỗi style không đồng nhất trong file */
#define SREC_ERROR_LENGTH -9 /* Lỗi độ dài bản ghi vượt quá hoặc nhỏ hơn quy định của định dạng Srecord */
#define SREC_ERROR_HEXA_VALUE -10 /* Lỗi xuất hiện ký tự không phải ký tự hexa trong file */
#define SREC_ERROR_TERMINATE -11 /* Lỗi không có bản ghi kết thúc hoặc bản ghi kết thúc không ở cuối file */

/* Hàm kiểm tra S0, bao gồm kiểm tra S0 đã tồn tại hay chưa và kiểm tra địa chỉ của S0 */
void SREC_Check_S0(bool *isS0Exist, int *listError, char s0Address[], bool *isLineError, bool *isFileError, int *countError)
{
    /* Nếu S0 đã tồn tại thì đánh dấu dòng này có lỗi, lưu lỗi vào danh sách lỗi */
    if (*isS0Exist == true)
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_MULTI_S0; /* Đưa lỗi vào danh sách lỗi */
    }

    /* Nếu S0 chưa tồn tại thì đánh dấu S0 */
    if (*isS0Exist == false)
    {
        *isS0Exist = true; /* Nếu S0 chưa tồn tại thì đánh dấu S0 tồn tại */
    }

    /* Nếu địa chỉ của S0 khác 0000 thì đánh dấu line này có lỗi, lưu lỗi vào danh sách lỗi */
    if (s0Address[0] != '0' || s0Address[1] != '0' || s0Address[2] != '0' || s0Address[3] != '0')
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_S0_ADDRESS; /* Đưa lỗi vào danh sách lỗi */
    }
}

/* Kiểm tra lỗi định dạng */
void SREC_CheckFormat(char buff[], int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    /* Nếu ký tự đầu tiên không bắt đầu bằng S hoặc ký tự type không nằm trong khoảng từ 0 -> 9 
    hoặc ký tự type trùng với type reserved S4 thì đánh dẫu lỗi định dạng */
    if (buff[0] != SREC_START || buff[1] < SREC_TYPE_S0 || buff[1] > SREC_TYPE_S9 || buff[1] == SREC_TYPE_S4)
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_FORMAT; /* Đưa lỗi vào danh sách lỗi */
    }
}

/* Kiểm tra lỗi byte count và đánh dấu lỗi vào danh sách lỗi nếu có */
void SREC_CheckByteCount(char buff[], int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    /* Chuyển đổi giá trị 2 ký tự 3, 4 từ hexa sang decimal */
    char byteCount_char[2];
    int byteCount = (int)strtoul(strncpy(byteCount_char, buff+2, 2), (char **)NULL, 16);
    
    /* Nếu số ký tự hex sau khi bỏ qua các trường S, Type, ByteCount và ký tự xuống dòng cuối cùng */
    /* khác byte count / 2 thì đánh dấu lỗi byte count không đồng nhất với số ký tự hex có trong dãy */
    if (byteCount != ((strlen(buff) - 5) / 2))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_BYTE_COUNT; /* Đưa lỗi vào danh sách lỗi */
    }
}

/* Nếu trong tệp xuất hiện dòng trống thì đánh dấu lỗi dòng trống và lưu vào danh sách lỗi */
bool SREC_CheckNewlineError(char buff[], int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    /* Kiểm tra lỗi dòng trống */
    if (strlen(buff) == 1)
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_NEWLINE; /* Đưa lỗi vào danh sách lỗi */
        return true; /* Nếu kiểm tra không có lỗi thì trả về true */
    }
    else
    {
        return false; /* Nếu kiểm tra có lỗi thì trả về false */
    }
}

/* Kiểm tra S0 đã tồn tại hay chưa, nếu chưa tồn tại thì thông báo lỗi và lưu lỗi vào danh sách lỗi */
bool SREC_Check_S0_Exist(bool *isS0Exist, int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    if (*isS0Exist == false)
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_S0_NOT_EXIST; /* Đưa lỗi vào danh sách lỗi */ 
        return false; /* Nếu kiểm tra có lỗi thì trả về false */
    }
    else
    {
        return true; /* Nếu kiểm tra không có lỗi thì trả về true */
    }
}

/* Kiểm tra giá trị hexa */
bool SREC_CheckHexaValue(char buff[], int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    int len = strlen(buff); /* Gán độ dài bản ghi vào biến len */
    int i; /* Biến đếm */
    bool check = true; /* Biến logic kiểm tra giá trị hexa */
    
    /* Duyệt lần lượt từng ký tự hexa */
    for (i = 2; i < len - 1; i++)
    {
        /* Nếu ký tự được duyệt không phải kiểu hexa thì đánh dấu lỗi */
        if (buff[i] < '0' || (buff[i] > '9' && buff[i] < 'A') || buff[i] > 'F')
        {
            *isLineError = true; /* Đánh dấu dòng có lỗi */
            *isFileError = true; /* Đánh dấu file có lỗi */
            *countError = *countError + 1; /* Tăng biến đếm số lỗi */
            listError[*countError] = SREC_ERROR_HEXA_VALUE; /* Đưa lỗi vào danh sách lỗi */ 
            check = false; /* Nếu kiểm tra có lỗi thì gán biến kiểm tra bằng false và dừng duyệt ký tự */ 
            break;
        }
    }

    return check; /* Trả về giá trị check */
    
}

/* Kiểm tra style của file, style được kiểm tra khi đã kiểm tra xong S0 đã tồn tại */
bool SREC_CheckStyle(char buff[], int *style, int *terminate, int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    /* Nếu style chưa được khởi tạo và bản ghi thuộc type S1 hoặc S2 hoặc S3 thì khởi tạo 
    giá trị style theo giá trị của trường type */
    if ((buff[1] == SREC_TYPE_S1 || buff[1] == SREC_TYPE_S2 || buff[1] == SREC_TYPE_S3) && *style == 0)
    {
        if (buff[1] == SREC_TYPE_S1)
        {
            *style = SREC_STYLE_S19; /* Nếu type bản ghi là S1 thì gán style bằng S19 */
            *terminate += 1; /* Tăng giá trị terminate lên 1, đánh dấu đã có style và chưa xuất hiện terminate */
            return true; /* Kiểm tra không có lỗi trả về giá trị true */
        }

        if (buff[1] == SREC_TYPE_S2)
        {
            *style = SREC_STYLE_S28; /* Nếu type bản ghi là S2 thì gán style bằng S28 */
            *terminate += 1; /* Tăng giá trị terminate lên 1, đánh dấu đã có style và chưa xuất hiện terminate */
            return true; /* Kiểm tra không có lỗi trả về giá trị true */
        }

        if (buff[1] == SREC_TYPE_S3)
        {
            *style = SREC_STYLE_S37; /* Nếu type bản ghi là S3 thì gán style bằng S37 */
            *terminate += 1; /* Tăng giá trị terminate lên 1, đánh dấu đã có style và chưa xuất hiện terminate */
            return true; /* Kiểm tra không có lỗi trả về giá trị true */
        }
    }
    /* Nếu style chưa được khởi tạo thì thông báo lỗi */
    else if (*style == 0)
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_STYLE; /* Đưa lỗi vào danh sách lỗi */ 
        return false; /* Kiểm tra có lỗi trả về giá trị false */
    }
    /* Nếu style đã được khởi tạo thì kiểm tra dòng được đọc có thuộc đúng style đã khởi tạo hay không
    và thông báo lỗi nếu có */
    else if (*style != 0)
    {
        /* Nếu style thuộc kiểu S19 mà giá trị type khác 1 hoặc 9 thì thông báo lỗi */
        if (*style == SREC_STYLE_S19 && (buff[1] != SREC_TYPE_S1 && buff[1] != SREC_TYPE_S9 && buff[1] != SREC_TYPE_S5 && buff[1] != SREC_TYPE_S6))
        {
            *isLineError = true; /* Đánh dấu dòng có lỗi */
            *isFileError = true; /* Đánh dấu file có lỗi */
            *countError = *countError + 1; /* Tăng biến đếm số lỗi */
            listError[*countError] = SREC_ERROR_STYLE; /* Đưa lỗi vào danh sách lỗi */ 
            return false; /* Kiểm tra có lỗi trả về giá trị false */
        }
        /* Nếu style thuộc kiểu S28 mà giá trị type khác 2 hoặc 8 thì thông báo lỗi */
        else if (*style == SREC_STYLE_S28 && (buff[1] != SREC_TYPE_S2 && buff[1] != SREC_TYPE_S8 && buff[1] != SREC_TYPE_S5 && buff[1] != SREC_TYPE_S6))
        {
            *isLineError = true; /* Đánh dấu dòng có lỗi */
            *isFileError = true; /* Đánh dấu file có lỗi */
            *countError = *countError + 1; /* Tăng biến đếm số lỗi */
            listError[*countError] = SREC_ERROR_STYLE; /* Đưa lỗi vào danh sách lỗi */ 
            return false; /* Kiểm tra có lỗi trả về giá trị false */
        }
        /* Nếu style thuộc kiểu S37 mà giá trị type khác 3 hoặc 7 thì thông báo lỗi */
        else if (*style == SREC_STYLE_S37 && (buff[1] != SREC_TYPE_S3 && buff[1] != SREC_TYPE_S7 && buff[1] != SREC_TYPE_S5 && buff[1] != SREC_TYPE_S6))
        {
            *isLineError = true; /* Đánh dấu dòng có lỗi */
            *isFileError = true; /* Đánh dấu file có lỗi */
            *countError = *countError + 1; /* Tăng biến đếm số lỗi */
            listError[*countError] = SREC_ERROR_STYLE; /* Đưa lỗi vào danh sách lỗi */ 
            return false; /* Kiểm tra có lỗi trả về giá trị false */
        }
        else
        {
            return true; /* Kiểm tra không có lỗi trả về giá trị true */
        }
    }
}

/* Kiểm tra độ dài mỗi bản ghi */
void SREC_CheckLength(char buff[], int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    int len; /* Biến lưu giá trị độ dài bản ghi được đọc */

    len = strlen(buff) - 1; /* Gán độ dài bản ghi trừ đi 1 ký tự xuống dòng cuối cùng vào biến */

    /* Nếu bản ghi thuộc type S0 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S0 && (len < SREC_S0_LENGTH_MIN || len > SREC_S0_LENGTH_MAX))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
    /* Nếu bản ghi thuộc type S1 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S1 && (len < SREC_S1_LENGTH_MIN || len > SREC_S1_LENGTH_MAX))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
    /* Nếu bản ghi thuộc type S2 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S2 && (len < SREC_S2_LENGTH_MIN || len > SREC_S2_LENGTH_MAX))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
    /* Nếu bản ghi thuộc type S3 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S3 && (len < SREC_S3_LENGTH_MIN || len > SREC_S3_LENGTH_MAX))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
    /* Nếu bản ghi thuộc type S5 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S5 && (len != SREC_S5_LENGTH))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
    /* Nếu bản ghi thuộc type S6 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S6 && (len != SREC_S6_LENGTH))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
    /* Nếu bản ghi thuộc type S7 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S7 && (len != SREC_S7_LENGTH))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
    /* Nếu bản ghi thuộc type S8 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S8 && (len != SREC_S8_LENGTH))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
    /* Nếu bản ghi thuộc type S9 và độ dài không nằm trong giới hạn cho phép thì đánh dấu lỗi */
    if (buff[1] == SREC_TYPE_S9 && (len != SREC_S9_LENGTH))
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_LENGTH; /* Đưa lỗi vào danh sách lỗi */ 
    }
}

/* Chuyển đổi 1 byte tương đương 2 ký tự hexa sang decimal */
int Hexa1Byte2Int(char hexa1Byte[])
{
    int i; /* Biến đếm */
    int integer = 0; /* Khởi tạo biến nguyên lưu giá trị decimal */
    for (i = 0; i < 2; i++)
    {
        /* Nếu ký tự được duyệt nằm trong đoạn từ '0' đến '9' thì đổi về giá trị int 
        và nhân với cơ số 16 */
        if (hexa1Byte[i] >= '0' && hexa1Byte[i] <= '9')
        {
            integer += ((int) hexa1Byte[i] - 48) * (16 - i * 15);
        }
        /* Nếu ký tự được duyệt nằm trong đoạn từ 'A' đến 'F' thì đổi về giá trị int 
        và nhân với cơ số 16 */
        if (hexa1Byte[i] >= 'A' && hexa1Byte[i] <= 'F')
        {
            integer += ((int) hexa1Byte[i] - 55) * (16 - i * 15);
        }
    }

    return integer; /* Trả về giá trị nguyên mang giá trị của 2 ký tự hexa */
}

/* Chuyển đổi kiểu decimal sang hexa, lưu lại 2 ký tự hexa LSB */
char* Int2Hexa1Byte(int integer)
{
    static char hexa[2]; /* Mảng tĩnh lưu giá trị bù 1 của 2 ký tự hexa */
    int q, r, i; /* Biến lưu giá trị thương, dư và biến đếm */

    /* Duyệt ngược từ giá trị LSB */
    for (i = 1; i >= 0; i--)
    {
        q = integer >> 4; /* Chia giá trị integer cho 4 */
        r = integer - q * 16; /* Lấy phần dư của phép chia */
        integer = q; /* Gán integer bằng thương, phục vụ cho phép chia tiếp theo */
        /* Nếu phần dư nhỏ hơn 10 */
        if (r < 10)
        {
            hexa[i] = r + 48; /* Chuyển thành ký tự char khoảng từ '0' đến '9' */
        }
        if (r >= 10)
        {
            hexa[i] = r + 55; /* Chuyển thành ký tự char khoảng từ 'A' đến 'F' */
        }
    }

    return hexa; /* Trả về 2 ký tự hexa sau khi đổi từ int */
}

/* Thực hiện bù 1 cho 2 ký tự hexa, tương đương 1 byte */
char* InverseByte(char hexa[])
{
    static char hexa_inverse[2]; /* Mảng tĩnh lưu giá trị bù 1 của 2 ký tự hexa */
    int i; /* Biến đếm */
    int temp; /* Biến lưu giá trị tạm thời*/
    for (i = 0; i < 2; i++)
    {
        /* Nếu ký tự được duyệt nằm trong khoảng '0' -> '9' */
        if (hexa[i] <= '9' && hexa[i] >= '0')
        {
            /* Đưa giá trị hexa kiểu char về giá trị integer. Lấy 15 trừ đi giá trị integer 
            để tìm được giá trị bù 1 của ký tự hexa và lưu vào biến tạm. Có hai trường hợp xảy ra:
            với giá trị biến tạm lớn hơn 10 thì cần đưa về kiểu ký tự char từ 'A' đến 'F', với giá
            trị biến tạm nhỏ hơn 10 thì đưa về kiểu ký tự char từ '0' đến '9' */
            temp = 15 - ((int)hexa[i] - 48); 
            if (temp >= 10)
            {
                hexa_inverse[i] = temp + 55; /* Nếu giá trị temp lớn hơn 10 thì chuyển thành ký tự char khoảng từ 'A' đến 'F' */
            }
            else
            {
                hexa_inverse[i] = temp + 48; /* Nếu giá trị integer nhỏ hơn 10 thì chuyển thành ký tự char khoảng từ '0' đến '9' */
            }
        }
        /* Nếu giá trị được duyệt nằm trong khoảng từ 'A' đến 'F' nghĩa là phần bù luôn nhỏ hơn 10 */      
        if (hexa[i] <= 'F' && hexa[i] >= 'A')
        {
            /* Đưa giá trị hexa kiểu char về giá trị integer. Lấy 15 trừ đi giá trị integer để tìm được 
            giá trị bù 1 của ký tự hexa và lưu vào biến tạm */
            temp = 15 - ((int)hexa[i] - 55); 
            hexa_inverse[i] = temp + 48; /* Chuyển thành ký tự char khoảng từ '0' đến '9' */
        }
    }

    return hexa_inverse; /* Trả về 2 ký tự hexa đã được bù 1 */
}

/* Kiểm tra checksum, đánh dấu lỗi và lưu vào danh sách lỗi nếu có */
int SREC_CheckChecksum(char buff[], int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    char *checksum; /* Biến chứa giá trị tính toán checksum */
    char hexa1Byte[2]; /* Mảng lưu từng gặp ký tự hexa tương đương 1 Byte */
    int checksumint; /* Biến lưu giá trị hệ decimal của checksum */
    int i; /* Biến đếm */
    int len = strlen(buff); /* Biến lưu giá trị độ dài bản ghi */

    /* Duyệt từng cặp ký tự hexa trong bản ghi */
    for (i = 2, checksumint = 0; i <= strlen(buff) - 5; i = i + 2)
    {
        strncpy(hexa1Byte, buff+i, 2); /* Cắt 2 ký tự hexa bắt đầu từ vị trí buff + i lưu vào mảng hexa1Byte */
        checksumint += Hexa1Byte2Int(hexa1Byte); /* Chuyển đổi giá trị 2 ký tự hexa vừa cắt về decimal và cộng với biến lưu giá trị decimal của checksum */
    }   
    checksum = Int2Hexa1Byte(checksumint); /* Chuyển đổi giá trị hệ decimal của checksum về 2 ký tự hexa LSB */
    checksum = InverseByte(checksum); /* Thực hiện bù 1 hai ký tự hexa vừa tìm được ở trên */

    /* So sánh 2 ký tự hexa cuối của bản ghi với checksum tìm được ở trên, nếu có sự khác biệt
    thì thêm lỗi vào danh sách lỗi */
    if (buff[len - 3] != checksum[0] || buff[len - 2] != checksum[1])
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_CHECKSUM; /* Đưa lỗi tìm được vào danh sách lỗi */
    }
}

/* Hàm kiểm tra terminate của file, trả về true nếu file đã có bản ghi terminate và trả về false
nếu file chưa có bản ghi terminate */
bool SREC_CheckTerminate(char buff[], int *style, int *terminate,  int *listError, bool *isLineError, bool *isFileError, int *countError)
{
    /* Nếu giá trị terminate = 2 tức là đã có bản ghi kết thúc file, thực hiện thêm lỗi
    vào danh sách và trả về giá trị true */
    if (*terminate == 2)
    {
        *isLineError = true; /* Đánh dấu dòng có lỗi */
        *isFileError = true; /* Đánh dấu file có lỗi */
        *countError = *countError + 1; /* Tăng biến đếm số lỗi */
        listError[*countError] = SREC_ERROR_TERMINATE; /* Đưa lỗi tìm được vào danh sách lỗi */
        return true; /* Trả về file đã có bản ghi terminate */
    }
    /* Nếu style của file là S19 và type bản ghi tiếp theo được đọc là S9 thì tăng giá trị terminate
    lên 1 đơn vị */
    if (*style == SREC_STYLE_S19 && buff[1] == SREC_TYPE_S9)
    {
        *terminate += 1; /* Tăng giá trị terminate lên 1 đơn vị */
        return false; /* Do lần đầu xuất hiện terminate nên trả về false do không có lỗi */
    }
    /* Nếu style của file là S28 và type bản ghi tiếp theo được đọc là S8 thì tăng giá trị terminate
    lên 1 đơn vị */
    else if (*style == SREC_STYLE_S28 && buff[1] == SREC_TYPE_S8)
    {
        *terminate += 1; /* Tăng giá trị terminate lên 1 đơn vị */
        return false; /* Do lần đầu xuất hiện terminate nên trả về false do không có lỗi */
    }
    /* Nếu style của file là S37 và type bản ghi tiếp theo được đọc là S7 thì tăng giá trị terminate
    lên 1 đơn vị */
    else if (*style == SREC_STYLE_S37 && buff[1] == SREC_TYPE_S7)
    {
        *terminate += 1; /* Tăng giá trị terminate lên 1 đơn vị */
        return false; /* Do lần đầu xuất hiện terminate nên trả về false do không có lỗi */
    }
    else 
    {
        return false; /* Nếu không có trường hợp nào kể trên đúng thì trả về false đánh dấu không có lỗi, terminate vẫn chưa xuất hiện */
    }
}

/* Hàm in lỗi của mỗi dòng nếu có từ danh sách lỗi lên màn hình */
void SREC_PrintError(char buff[], int *listError, int *lineNumber, int *countError)
{
    int i; /* Biến đếm */
    
    /* Duyệt số lỗi và lỗi có trong mảng */
    for (i = 0; i <= *countError; i++)
    {
        switch (listError[i])
        {
        /* Nếu xuất hiện lỗi định dạng thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_FORMAT:
            printf("\n Line %d : Format error", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi dòng mới bị rỗng thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_NEWLINE:
            printf("\n Line %d : Newline error", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi nhiều bản ghi S0 thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_MULTI_S0:
            printf("\n Line %d : Multi S0 error", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi địa chỉ bản ghi S0 không chính xác thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_S0_ADDRESS:
            printf("\n Line %d : S0 address error", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi byte count thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_BYTE_COUNT:
            printf("\n Line %d : Byte count error", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi checksum thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_CHECKSUM:
            printf("\n Line %d : Checksum error", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi không tồn tại bản ghi S0 thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_S0_NOT_EXIST:
            printf("\n Line %d : S0 not exist", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi style thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_STYLE:
            printf("\n Line %d : Style error", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi độ dài bản ghi thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_LENGTH:
            printf("\n Line %d : Length error", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi giá trị hexa thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_HEXA_VALUE:
            printf("\n Line %d : Invalid hexa value", *lineNumber);
            break;
        /* Nếu xuất hiện lỗi tồn tại nhiều hơn 1 bản ghi terminate thì in tên lỗi ra màn hình kèm theo vị trí dòng bị lỗi */
        case SREC_ERROR_TERMINATE:    
            printf("\n Line %d : Termination record has already existed", *lineNumber);
            break;
        
        default:
            break;
        }
    }
    printf("\n %s", buff); /* In ra màn hình giá trị dòng bị lỗi */
}

/* Hàm ghi giá trị địa chỉ và dữ liệu từ file input vào file output */
void WritingToOutputFile(FILE *file_input, FILE *file_output, char buff[])
{
    int len; /* Biến lưu độ dài mảng bộ đệm */
    char space = ' '; /* Ký tự khoảng trống*/
    char newline = '\n'; /* Ký tự xuống dòng */
    char address[SREC_ADDRESS_32_BIT + 1]; /* Mảng chứa địa chỉ, tối đa 8 ký tự hexa tương đương 32 bit */
    char data[SREC_DATA_LENGTH_MAX + 1]; /* Mảng chứa dữ liệu, tối đa 64 ký tự hexa tương đương 32 Byte */
    int address_start = 1 + SREC_TYPE_LENGTH + SREC_BYTE_COUNT_LENGTH; /* Vị trí bắt đầu của trường địa chỉ */
    int data_16bit_address_start = address_start + SREC_ADDRESS_16_BIT; /* Vị trí bắt đầu của trường dữ liệu với 16 bit địa chỉ */
    int data_24bit_address_start = address_start + SREC_ADDRESS_24_BIT; /* Vị trí bắt đầu của trường dữ liệu với 24 bit địa chỉ */
    int data_32bit_address_start = address_start + SREC_ADDRESS_32_BIT; /* Vị trí bắt đầu của trường dữ liệu với 32 bit địa chỉ */

    /* Reset phần tử của mảng về null */
    memset(address, '\0', (SREC_ADDRESS_32_BIT + 1) * sizeof(char));
    memset(data, '\0', (SREC_DATA_LENGTH_MAX + 1) * sizeof(char));

    fputs("Address\t\t\t\tData\n", file_output); /* Ghi tên cột địa chỉ và dữ liệu */

    /* Kiểm tra điều kiện kết thúc file */
    while (!feof(file_input))
    {
        fgets(buff, SREC_SIZE, (FILE*)file_input); /* Đọc giá trị từ file vào mảng bộ đệm */
        len = strlen(buff); /* Trả về độ dài của mảng bộ đệm */

        /* Nếu mảng không chứa phần tử thì thoát khỏi vòng lặp */
        if (len == 0)
        {
            break;
        }

        /* Nếu type của bản ghi là S0 thì chỉ ghi giá trị địa chỉ vào file output */
        if (buff[1] == SREC_TYPE_S0)
        {
            /* Cắt 16 bit địa chỉ tương ứng 4 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_16_BIT);  
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output */ 
            fputc(newline, file_output); /* Ghi ký tự xuống dòng vào file output */
        }
        /* Nếu type của bản ghi là S1 thì ghi giá trị địa chỉ và dữ liệu vào file output */
        if (buff[1] == SREC_TYPE_S1)
        {
            /* Cắt 16 bit địa chỉ tương ứng 4 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_16_BIT);
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output */
            fputc(space, file_output); /* Ghi ký tự khoảng trống vào file output */
            /* Cắt các ký tự hexa bắt đầu từ vị trí bắt đầu của dữ liệu, bỏ qua 2 ký tự checksum cuối cùng rồi đưa vào mảng dữ liệu */
            strncpy(data, buff + data_16bit_address_start, len - 5 - SREC_CHECKSUM_LENGTH - SREC_ADDRESS_16_BIT);
            fputs(data, file_output); /* Ghi giá trị lưu trong mảng data vào file output*/
            fputc(newline, file_output); /* Ghi ký tự xuống dòng vào file output */
        }
        /* Nếu type của bản ghi là S2 thì ghi giá trị địa chỉ và dữ liệu vào file output */
        if (buff[1] == SREC_TYPE_S2)
        {
            /* Cắt 24 bit địa chỉ tương ứng 6 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_24_BIT);
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output */
            fputc(space, file_output); /* Ghi ký tự khoảng trống vào file output */
            /* Cắt các ký tự hexa bắt đầu từ vị trí bắt đầu của dữ liệu, bỏ qua 2 ký tự checksum cuối cùng rồi đưa vào mảng dữ liệu */
            strncpy(data, buff + data_24bit_address_start, len - 5 - SREC_CHECKSUM_LENGTH - SREC_ADDRESS_24_BIT);
            fputs(data, file_output); /* Ghi giá trị lưu trong mảng data vào file output*/
            fputc(newline, file_output); /* Ghi ký tự xuống dòng vào file output */
        }
        /* Nếu type của bản ghi là S3 thì ghi giá trị địa chỉ và dữ liệu vào file output */
        if (buff[1] == SREC_TYPE_S3)
        {
            /* Cắt 32 bit địa chỉ tương ứng 8 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_32_BIT);
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output */
            fputc(space, file_output); /* Ghi ký tự khoảng trống vào file output */
            /* Cắt các ký tự hexa bắt đầu từ vị trí bắt đầu của dữ liệu, bỏ qua 2 ký tự checksum cuối cùng rồi đưa vào mảng dữ liệu */
            strncpy(data, buff + data_32bit_address_start, len - 5 - SREC_CHECKSUM_LENGTH - SREC_ADDRESS_32_BIT);
            fputs(data, file_output); /* Ghi giá trị lưu trong mảng data vào file output*/
            fputc(newline, file_output); /* Ghi ký tự xuống dòng vào file output */
        }
        /* Nếu type của bản ghi là S5 thì chỉ ghi giá trị địa chỉ vào file output */
        if (buff[1] == SREC_TYPE_S5)
        {
            /* Cắt 16 bit địa chỉ tương ứng 4 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_16_BIT);
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output */
            fputc(newline, file_output); /* Ghi ký tự xuống dòng vào file output */
        }
        /* Nếu type của bản ghi là S6 thì chỉ ghi giá trị địa chỉ vào file output */
        if (buff[1] == SREC_TYPE_S6)
        {
            /* Cắt 24 bit địa chỉ tương ứng 6 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_24_BIT);
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output */
            fputc(newline, file_output); /* Ghi ký tự xuống dòng vào file output */
        }
        /* Nếu type của bản ghi là S7 thì chỉ ghi giá trị địa chỉ vào file output */
        if (buff[1] == SREC_TYPE_S7)
        {
            /* Cắt 32 bit địa chỉ tương ứng 8 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_32_BIT);
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output */
            fputc(newline, file_output); /* Ghi ký tự xuống dòng vào file output */
        }
        /* Nếu type của bản ghi là S8 thì chỉ ghi giá trị địa chỉ vào file output */
        if (buff[1] == SREC_TYPE_S8)
        {
            /* Cắt 24 bit địa chỉ tương ứng 6 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_24_BIT);
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output */
            fputc(newline, file_output);
        }
        /* Nếu type của bản ghi là S9 thì chỉ ghi giá trị địa chỉ vào file output */
        if (buff[1] == SREC_TYPE_S9)
        {
            /* Cắt 16 bit địa chỉ tương ứng 4 ký tự hexa, bắt đầu từ vị trí bắt đầu của địa chỉ đưa vào mảng address */
            strncpy(address, buff + address_start, SREC_ADDRESS_16_BIT);
            fputs(address, file_output); /* Ghi giá trị lưu trong mảng address vào file output*/
            fputc(newline, file_output); /* Ghi ký tự xuống dòng vào file output */
        }

        /* Reset lại phần tử của mảng về NULL */
        memset(address, '\0', SREC_ADDRESS_32_BIT * sizeof(char));
        memset(data, '\0', SREC_DATA_LENGTH_MAX * sizeof(char));
        memset(buff, '\0', SREC_SIZE * sizeof(char));
    }    
}

#endif