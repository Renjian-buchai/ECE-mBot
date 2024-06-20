#if !defined(OUTPUT_HH)
#define OUTPUT_HH

#define DEBUG 1

#if DEBUG

#define LOG(x) Serial.println(x)

#else

#define LOG(x) (void)0

#endif

#endif