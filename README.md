arduino
=======

Random Arduino experiments. 

Introduction
------------

One of the cool things about an [Arduino](http://www.arduino.cc/) is that you can use it as a cheap, fully programmable analog-to-digital converter. However, some ADC uses require a very high sampling rate. For example, if you wanted to implement a VLF metal detector in software on an Arduino, you would need to be able to accurately sample a signal with a frequency somewhere in the 3kHz to 30kHz range. So what is the maximum analog signal sampling rate on an Arduino?

Step 1: Basic Implementation
----------------------------

The `analogReadBasic` sketch uses the standard [analogRead](http://arduino.cc/en/Reference/analogRead) function to sample the analog signal. It achieves a sampling rate of **8.3 kHz** on my Arduino Duemilanove.

Step 2: Add Custom Prescale
---------------------------

The [ATmega328 microcontroller](http://www.atmel.com/Images/doc8161.pdf) in the Duemilanove has a customizable ADC prescale factor that allows the user to sacrifice accuracy for speed. The prescale factor can be set to a value between 2 (fastest and least accurate) and 128 (slowest and most accurate). The default setting is 128 (slow and accurate).

In my testing, a prescale setting of 16 seemed to offer the best accuracy/speed tradeoff. Modifying the basic implementation to use an ADC prescale factor of 16 in the `analogReadWithPrescale` sketch resulted in a sampling rate of **43.3 kHz**.

Step 3: Add Direct Access
-------------------------

The built-in [analogRead](http://arduino.cc/en/Reference/analogRead) function adds a little bit of overhead to analog signal sampling. Additionally, the ATmega328 microcontroller writes the ADC sample result to two registers (`ADCL` and `ADCH`) with 10-bit precision. However, if 8-bit precision is sufficient, then only one of these registers (`ADCH`) need be read after each sample, resulting in a faster overall sampling rate.

Replacing the calls to `analogRead` with direct access to the `ADCH` register in the `analogReadWithPrescaleDirectAccess` sketch results in an overall sampling rate of **47.5 kHz**, with the above mentioned negative impact on precision.

Step 4: Add Custom Loop
-----------------------

The built-in [loop](http://arduino.cc/en/Reference/loop) callback is intended to provide a standard location for Arduino program logic. However, it's easy to imagine that there might be some overhead associated with this ease-of-use. Unsuprisingly, this appears to be the case, and calling the function directly in a loop in the [setup](http://arduino.cc/hu/Reference/Setup) function appears to bump the sampling rate up to **52.5 kHz**. See the `analogReadWithPrescaleDirectAccessCustomLoop` sketch for more details.

More?
-----

The code contains links to other discussions and implementations that might be useful in understanding some of these tweaks.

If you know of any other tricks that can bump up the analog sampling rate, please let me know!
