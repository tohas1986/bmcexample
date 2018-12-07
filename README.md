# bmcexample

## Faraday

Для корректной работы NIC1, подключенного к BMC:
- папку faraday из этого хранилища скопировать (с заменой) в папку по адресу:
```
linux-aspeed/drivers/net/ethernet/faraday
```

Ну и собственно все

## Rikor-Machine

Рецепт rikor-machine содержит патчи для u-boot и linux-aspeed. Папку rikor-machine нужно скопировать в папку рецептов. Патчи применяются автоматически при выполнении команды devtool modify, или при сборки из сети.

Для u-boot изменяется файл
```
u-boot/config/fbyosemite_defconfig
```

Для linux-aspeed изменяется файл
```
linux-aspeed/arch/arm/plat-aspeed/dev-i2c.c
linux-aspeed/drivers/net/ethernet/faraday/ftgmac100.c
```

## dscan - сканирование устройств i2c

_R-BD-E5R-V4 i2c devices scanner_

[Описание dscan](https://github.com/ShajTester/dscan/blob/master/README.md)

Рецепт находится в `recipes-example/dscan`.

В `recipes-example/dscan/files/dscan.conf` находится конфигурация.

`recipes-example/dscan/dscan_0.1.bb` - рецепт для сборки самой утилиты.

`recipes-example/dscan/dscan_%.bbappend` - рецепт для конфигурации.

### Использование

Сканирование известных устройств, описанных в конфигурации `/etc/dscan/dscan.conf`, и вывод отчета простым текстом:
```
dscan
```

Вывод отчета в json:
```
dscan --json1
```

Использование альтернативной конфигурации:
```
dscan -c my-i2c.conf --json1
```

## Пример работы с АЦП

fadc - демон, работающий с АЦП


