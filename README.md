# АВС: Курсовая работа
Курсовая работа по дисциплине "Архитектура вычислительных систем" (БГУИР, ФКСиС, ИиТП, 5 семестр)

#### Тема
Скрытая фиксация ввода текста с клавиатуры

#### Студент
Толкачёв Денис Степанович, *гр. 753504*

#### Контакты
*Telegram:* [@dtalkachou][telegram]

*E-Mail:* <dtalkachou@ya.ru>

___

# Запуск
Для сборки проекта рекомендуется Visual Studio 2017 и старше. Также можно [скачать готовый exe-файл][download] и понаблюдать за работой программы.

**P.S.** Т.к. программа работает в «скрытом» режиме, то просто закрыть её не получится. Для этого подойдёт, например, диспетчер задач.

# Результат работы
Для демонстрации результата работы я выполнял следующие действия:
1. В новой вкладке **Google Chrome** ввёл запрос *«Test request»* и нажал клавишу *RETURN*;
2. В загрузившемся окне ввёл запрос *«other request»* и так же подтвердил запрос клавишей *RETURN*.

Вот результат работы программы (содержимое файла Logger.txt):

```
[Новая вкладка - Google Chrome - at Sun Dec 15 18:20:12 2019]
Test[SPACE] request[RETURN]

[Test request - Поиск в Google - Google Chrome - at Sun Dec 15 18:20:28 2019]
other[SPACE] request[RETURN]
```

Можно заметить, что программа распознает окна, в которых были нажаты клавиши. В случае, если рабочее окно было изменено, программа пишет новый заголовок и фиксирует нажатия клавиш. Программа без каких-либо проблем распознаёт регистры нажатых клавиш (учитывая различные комбинации *SHIFT* и *CAPS*), так что «украсть» чей-нибудь пароль не составит особого труда. Конечно, программа в точности пишет истории зажатых клавиш, убедиться в этом можно запустив программу самостоятельно.

# Недостатки
* Программа не распознает текущую раскладку клавиатуры, все фиксации происходят на английской раскладке.
* Программа обрабатывает не все «вспомогательные» клавиши, а только основные: *RETURN*, *SHIFT* и т.д.
* История фиксаций храниться локально и никуда не отправляется.

В условиях курсового проекта не стояло задач реализовывать функционал перечисленный выше, однако, при необходимости, его всегда можно дополнить.

<!-- Attachments -->
[telegram]: https://t.me/dtalkachou
[download]: https://yadi.sk/d/fD7Bce8VB1tWUQ
