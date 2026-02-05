# DEEPCRAFT Studio 5.8.4292+50129d917517243fc033cba30ce355705c84a08c
# Copyright © 2023- Imagimob AB, All Rights Reserved.
# 
# Generated at 02/03/2026 07:40:02 UTC. Any changes will be lost.
# 
# Layer                          Shape           Type       Function
# Sliding Window (data points)   [96,2]          float      dequeue
# Contextual Window (Sliding Window) [96,2]          float      dequeue
# 

import numpy as np
import enum

_K5 = np.empty((1744), dtype=np.int8)	# byte (8 bit) 


class ReturnStatus(enum.Enum): 
    RET_SUCCESS = 0
    RET_NODATA = -1
    RET_NOMEM = -2

class SlidingWindowTime:
    def __init__(self, input_size: int, window_count : int):
        self._data_buffer = []
        self._time_buffer = []
        self._data_buffer_size = input_size * window_count
        self._input_size = input_size
        self._window_count = window_count
            
    def enqueue(self, data, time):
    
        self._data_buffer.extend(data.flatten())

        if len(self._data_buffer) > self._data_buffer_size:
            return ReturnStatus.RET_NOMEM                

        self._time_buffer.extend([time.flatten().min(), time.flatten().max()])
        return ReturnStatus.RET_SUCCESS

    def dequeue(self, data_out, data_stride: int, time_out):
        data_window_size = np.prod(data_out.shape)
        if len(self._data_buffer) >= data_window_size:
            data_window = np.array(self._data_buffer[:data_window_size]).reshape(data_out.shape)
            np.copyto(data_out, data_window)
            del self._data_buffer[:(data_stride * self._input_size)]
           
            timestamp_count = 2 * self._window_count;
            time_window = np.array(self._time_buffer[:timestamp_count]).reshape(timestamp_count)
            time_out[0] = time_window.min()
            time_out[1] = time_window.max()
            del self._time_buffer[:2 * data_stride]
            
            return ReturnStatus.RET_SUCCESS

        return ReturnStatus.RET_NODATA


class Model:
    def __init__(self):
        self._K5 = SlidingWindowTime(2, 96)
        self.data_in_count = 2
        self.data_in_shape = (2)
        self.time_in_count = 1
        self.time_in_shape = (1)
        self.data_out_count = 192
        self.data_out_shape = (96,2)
        self.time_out_count = 2
        self.time_out_shape = (2)
        self.api = 'queue'

    def enqueue(self, data_in : np.array, time_in : np.array):
        """
        Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
        
        Parameters:
         data_in(float[2]): DESCRIPTION. [2]
         time_in(float[1]): DESCRIPTION. [1]
        """
        
        return_status = self._K5.enqueue(data_in, time_in)
        if return_status != ReturnStatus.RET_SUCCESS:
            return return_status
        
        return ReturnStatus.RET_SUCCESS

    def dequeue(self, data_out : np.array, time_out : np.array):
        """
        Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
        
        Parameters:
         data_out(float[192]): DESCRIPTION. [96,2]
         time_out(float[2]): DESCRIPTION. [2]
        """
        
        return_status = self._K5.dequeue(data_out.reshape([96,2]), 6, time_out.reshape([2]))
        if return_status != ReturnStatus.RET_SUCCESS:
            return return_status
        
        return ReturnStatus.RET_SUCCESS

