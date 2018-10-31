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

## Пример работы с АЦП

fadc - демон, работающий с АЦП


