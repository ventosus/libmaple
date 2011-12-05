#include <stddef.h>             // for ptrdiff_t

#include "wirish.h"
#include "fsmc.h"

#ifndef BOARD_maple_native
#error "Sorry, this example only works on Maple Native."
#endif

#define COMM Serial2

// Start of FSMC SRAM bank 1
static uint16 *const sram_start = (uint16*)0x60000000;
// Random safe address to write to in Oak's notional SRAM bank
static uint16 *const sram_end   = (uint16*)0x60000040;

#define DATA_MASK (~BIT(7))

bool test_single_write(uint16*, const uint16, bool verbose=true);
void test_all_bits(void);
void test_all_addresses(void);

void setup() {
    Serial2.begin(115200);
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, HIGH);
    COMM.println("*** Beginning tests.");
}

void loop() {
    static int count = 0;
    // while (!COMM.available()) {
        // toggleLED();
        // delay(100);
    // }
    // COMM.read();
    test_all_bits();
    count++;
    if (count % 8192 == 0) {
        COMM.println(count);
    }
    // COMM.println("* Finished test round. Press a key to go again.");
}

#define NBITS 16
void test_all_bits(void) {
    static uint16 *ptr = sram_start;
    static uint16 vals[NBITS] = {
        0x1, 0x2, 0x4, 0x8,            // Bits 0--3
        0x10, 0x20, 0x40, 0x80,        // Bits 4--7
        0x100, 0x200, 0x400, 0x800,    // Bits 8--11
        0x1000, 0x2000, 0x4000, 0x8000 // Bits 12--15
    };

    // COMM.print("* Testing address 0x");
    // COMM.print((uint32)ptr, HEX);
    // COMM.println("...");

    // bool ok = true;
    for (unsigned b = 0; b < NBITS; b++) {
        // ok = ok &&
            test_single_write(ptr, vals[b], false);
    }

    // if (ok) {
    //     COMM.println("* OK!");
    // }

    ptr++;
    if (ptr >= sram_end) {
        ptr = sram_start;
    }
}

bool test_single_write(uint16 *ptr, const uint16 val, bool verbose) {
    uint16 tmp;

    if (verbose) {
        COMM.print("Writing; address=0x");
        COMM.print((uint32)ptr, HEX);
        COMM.print(", value=0x");
        COMM.print(val, HEX);
    }
    *ptr = val;
    if (verbose) {
        COMM.print(". Reading; ");
    }
    tmp = *ptr;
    if (verbose) {
        COMM.print("got: 0x");
        COMM.print(tmp, HEX);
        COMM.print(" [0x");
        COMM.print(tmp & DATA_MASK, HEX);
        COMM.println("]");
    }

    if ((tmp & DATA_MASK) != (val & DATA_MASK)) {
        COMM.print("** ERROR: At ptr=0x");
        COMM.print((uint32)ptr, HEX);
        COMM.print(", wrote 0x");
        COMM.print(val, HEX);
        COMM.print(" [0x");
        COMM.print(val & DATA_MASK);
        COMM.print("], but read 0x");
        COMM.print(tmp, HEX);
        COMM.print(" [0x");
        COMM.print(tmp & DATA_MASK, HEX);
        COMM.print("]");
        return false;
    }
    return true;
}

void test_all_addresses() {
    uint32 start, end;
    uint16 count = 0;
    uint16 *ptr;

    COMM.println("Now writing all memory addresses (unrolled loop)");
    start = micros();
    for (ptr = sram_start; ptr < sram_end;) {
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
    }
    end = micros();
    COMM.print("Done. Elapsed time (us): ");
    COMM.println(end - start);

    COMM.println("Validating writes.");
    for (ptr = sram_start, count = 0; ptr < sram_end; ptr++, count++) {
        uint16 value = *ptr;
        if (value != count) {
            COMM.print("mismatch: 0x");
            COMM.print((uint32)ptr);
            COMM.print(" = 0x");
            COMM.print(value, HEX);
            COMM.print(", should be 0x");
            COMM.print(count, HEX);
            COMM.println(".");
            ASSERT(0);
        }
    }
    COMM.println("Done; all writes seem valid.");

    ptrdiff_t nwrites = sram_end - sram_start;
    double us_per_write = double(end-start) / double(nwrites);
    COMM.print("Number of writes = ");
    COMM.print(nwrites);
    COMM.print("; avg. time per write = ");
    COMM.print(us_per_write);
    COMM.print(" us (");
    COMM.print(1 / us_per_write);
    COMM.println(" MHz)");
}

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
