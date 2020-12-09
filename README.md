# TowerStack
>  little tower stack game using LED matrix 

![image_hardware](images/TowerStack.GIF?raw=true)
YouTube: [![Youtube](https://img.youtube.com/vi/gG0TiHAeOdA/hqdefault.jpg)](https://youtu.be/gG0TiHAeOdA)
## Hardware 
* Elegoo uno R3 / ATmega328P ([amazon](https://www.amazon.de/gp/product/B01EWOE0UU/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1))
* LED matrix ([amazon](https://www.amazon.de/gp/product/B01BUTAFW2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1))
* lever ([amazon](https://www.amazon.de/gp/product/B00J2N3D78/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1))

## Wiring

```
Matrix 
  LC_LOAD_PIN: Pin 10
  LC_CLK_PIN: Pin 11
  LC_DIN_PIN: Pin 12
  GND
  VCC
  
Lever
  DATA_PIN: Pin 13
  GND
  VCC

```

## Level
```
animation_speed = 150 - (tower_height * 4);
```
