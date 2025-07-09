@echo off
:: Правильное объединение keybindings.json без ошибок формата
:: Автоматически обрабатывает пустые файлы и сохраняет валидный JSON

set VSCODE_KEYBINDINGS=%APPDATA%\Code\User\keybindings.json
set PROJECT_KEYBINDINGS=%~dp0.vscode\keybindings.json

:: Проверка существования файла
if not exist "%PROJECT_KEYBINDINGS%" (
    echo ОШИБКА: Файл .vscode\keybindings.json не найден!
    pause
    exit /b 1
)

:: Создаем временный файл для результата
set TEMP_RESULT=%TEMP%\vscode_keys_result.json

:: Основная логика обработки
(
    echo [
    
    :: Если основной файл существует, добавляем его содержимое (без скобок)
    if exist "%VSCODE_KEYBINDINGS%" (
        type "%VSCODE_KEYBINDINGS%" | find /v "[" | find /v "]"
    )
    
    :: Добавляем запятую между существующими и новыми keybindings
    if exist "%VSCODE_KEYBINDINGS%" if %%~z1 GTR 0 echo ,
    
    :: Добавляем новые keybindings (без скобок)
    type "%PROJECT_KEYBINDINGS%" | find /v "[" | find /v "]"
    
    echo ]
) > "%TEMP_RESULT%"

:: Заменяем оригинальный файл
move /Y "%TEMP_RESULT%" "%VSCODE_KEYBINDINGS%" >nul

echo Keybindings успешно объединены!
echo Перезапустите VS Code для применения изменений.
pause