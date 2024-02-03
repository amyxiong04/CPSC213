#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <assert.h>
#include "uthread.h"
#include "queue.h"
#include "disk.h"

queue_t pending_read_queue;
int num_reads;
int current_block_value;

void interrupt_service_routine() {
  void* resultv;
  void (*callback)(void*,void*);
  queue_dequeue (pending_read_queue, &resultv, NULL, &callback);
  callback (resultv, NULL);
}

void handleOtherReads(void *resultv, void *countv) {
  num_reads--;
  current_block_value = *(int*) resultv;
  if (num_reads == 0) {
    printf("%i\n", current_block_value);
    exit(EXIT_SUCCESS);
  } else {
    disk_schedule_read(&current_block_value, current_block_value);
    queue_enqueue(pending_read_queue, &current_block_value, 0, handleOtherReads);
  }
}

void handleFirstRead(void *resultv, void *countv) {
  num_reads = *(int*) resultv;
  current_block_value = *(int*) resultv;

  disk_schedule_read(&current_block_value, current_block_value);
  queue_enqueue(pending_read_queue, &current_block_value, 0, handleOtherReads);
}

int main(int argc, char **argv) {
  // Command Line Arguments
  static char* usage = "usage: treasureHunt starting_block_number";
  int starting_block_number;
  char *endptr;
  if (argc == 2)
    starting_block_number = strtol (argv [1], &endptr, 10);
  if (argc != 2 || *endptr != 0) {
    printf ("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init (1);
  disk_start (interrupt_service_routine);
  pending_read_queue = queue_create();

  // Start the Hunt
  disk_schedule_read(&current_block_value, starting_block_number);
  queue_enqueue(pending_read_queue, &current_block_value, 0, handleFirstRead);
  while (1); // infinite loop so that main doesn't return before hunt completes
}
