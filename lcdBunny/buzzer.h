#ifndef buzzer_included
#define buzzer_included


void buzzer_init();
void buzzer_set_period(short cycles);
short hz_to_cycles(short hz);
void play_hz(short hz);


#endif // included
