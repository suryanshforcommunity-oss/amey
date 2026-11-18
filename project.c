#include <stdio.h>

#define SIZE 5

typedef struct {
    float temperature;
    float humidity;
    float pressure;
} SensorData;

SensorData queue[SIZE];
int front = 0, rear = -1, count = 0;

void enqueue(float t, float h, float p) {
    if (count == SIZE) {
        printf("Buffer Overflow! Queue is full.\n");
        return;
    }

    rear = (rear + 1) % SIZE;
    queue[rear].temperature = t;
    queue[rear].humidity = h;
    queue[rear].pressure = p;
    count++;

    printf("Sensor reading inserted successfully.\n");
}

void dequeue(void) {
    if (count == 0) {
        printf("Buffer Underflow! Queue is empty.\n");
        return;
    }

    printf("Temperature: %.2f C\n", queue[front].temperature);
    printf("Humidity: %.2f %%\n", queue[front].humidity);
    printf("Pressure: %.2f hPa\n", queue[front].pressure);

    front = (front + 1) % SIZE;
    count--;
}

void display(void) {
    if (count == 0) {
        printf("Buffer is empty.\n");
        return;
    }

    printf("\nStored Sensor Readings:\n");
    for (int i = 0; i < count; i++) {
        int index = (front + i) % SIZE;
        printf("\nReading %d\n", i + 1);
        printf("Temperature: %.2f C\n", queue[index].temperature);
        printf("Humidity: %.2f %%\n", queue[index].humidity);
        printf("Pressure: %.2f hPa\n", queue[index].pressure);
    }
}

int main(void) {
    int choice;
    float t, h, p;

    do {
        printf("\n--- IoT Sensor Data Buffer ---\n");
        printf("1. Add Sensor Reading\n");
        printf("2. Process Oldest Reading\n");
        printf("3. Display Buffer\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            return 1;

        switch (choice) {
            case 1:
                printf("Enter temperature (C): ");
                if (scanf("%f", &t) != 1) return 1;
                printf("Enter humidity (%%): ");
                if (scanf("%f", &h) != 1) return 1;
                printf("Enter pressure (hPa): ");
                if (scanf("%f", &p) != 1) return 1;
                enqueue(t, h, p);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
