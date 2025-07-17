#include <windows.h>
#include <string.h>
#include <stdio.h>

#pragma comment(lib, "Shell32.lib")

// Простая base64 таблица
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Функция декодирования base64
int base64_decode(const char *in, unsigned char *out, int outlen) {
    int val = 0, valb = -8;
    int len = 0;
    for (; *in; ++in) {
        const char *p = strchr(base64_table, *in);
        if (!p) continue;
        val = (val << 6) + (p - base64_table); // Я вообще не понимаю почему ругается у меня тут
        valb += 6;
        if (valb >= 0) {
            if (len < outlen) {
                out[len++] = (char)((val >> valb) & 0xFF);
            }
            valb -= 8;
        }
    }
    return len;
}

int main() {
    // Исходный код (в base64)
    const char* encoded_script = "ВАШ КОД BASE64 ЗДЕСЬ";

    // Буфер для расшифрованного скрипта
    char script[1024] = {0};
    base64_decode(encoded_script, (unsigned char*)script, sizeof(script)-1);

    // Собираем команду
    char cmd[2048] = "powershell.exe -ExecutionPolicy Bypass -Command \"";
    strcat(cmd, script);
    strcat(cmd, "\"");

    // Запуск
    WinExec(cmd, SW_HIDE);
    return 0;
}
