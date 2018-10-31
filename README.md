# bmcexample

## Faraday

Для корректной работы NIC1, подключенного к BMC:
- папку faraday из этого хранилища скопировать (с заменой) в папку по адресу:
/linux-aspeed/drivers/net/ethernet/faraday

Ну и собственно все

## Rikor-Machine

Рецепт rikor-machine содержит патчи для u-boot и linux-aspeed.

Для u-boot изменяется файл
```
build/workspace/sources/u-boot/config/fbyosemite_defconfig
```

Для linux-aspeed изменяется файл
```
build/workspace/sources/linux-aspeed/arch/arm/plat-aspeed/dev-i2c.c
```

## Пример работы с АЦП

fadc - демон, работающий с АЦП


