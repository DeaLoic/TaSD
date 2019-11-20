#ifndef __MODELING_H__
#define __MODELING_H__

#include "queue_list.h"
#include "logic.h"
#include "info.h"
#include "request.h"

#define MAX_PROC_TIME 1
#define MAX_INCOME_TIME 4
#define TARGET_OUTPUT_REQUEST 1000
#define COUNT_OF_CYCLE 1

int next_cycle(queue_list_t *queue, free_zone_t *free_zone, info_t *info, request_t *next_request);
int model(queue_list_t *queue, free_zone_t *free_zone, info_t *info);

#endif