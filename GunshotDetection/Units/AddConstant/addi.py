#pragma IMAGINET_INCLUDES_BEGIN
import numpy as np
#pragma IMAGINET_INCLUDES_END

#pragma IMAGINET_FRAGMENT_BEGIN "addi"

def addi(input, value, output):
    np.add(input, [value], out=output)

#pragma IMAGINET_FRAGMENT_END

