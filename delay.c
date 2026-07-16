void delay_us(unsigned int delay)
{
delay*=12;
while(delay--);
}
void delay_ms(unsigned int delay)
{
delay*=12000;
while(delay--);
}
void delay_s(unsigned int delay)
{
delay*=12000000;
while(delay--);
}
