void blink_led(ap_uint<1> i_led_switch, ap_uint<4> *o_led);

int main() {
    ap_uint<4> led;
    ap_uint<1> sw;

    for(int i=0; i<10; i++){
        blink_led(sw, &led);
    }
    return 0;
}