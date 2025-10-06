import cv2


# insert the path to your Royale installation here:
# note that you need to use \\ or / instead of \ on Windows
#modify by your own path
# ROYALE_DIR = "C:\\Sheng\\tof\\0924_for_dev\\5.12.0.3089_royale\\python"
# sys.path.append(ROYALE_DIR)


def show_overlay(grayImage, zImage):
    # Normalize the 32-bit depth image to a range of 0 to 255 for visualization
    depth_normalized = zImage
    # depth_normalized = np.flip(depth_normalized, (0, 1))
    depth_normalized = cv2.normalize(depth_normalized, None, 0, 255, cv2.NORM_MINMAX)
    depth_normalized = cv2.convertScaleAbs(depth_normalized)
    # depth_normalized = np.uint8(depth_normalized)  # Convert to 8-bit after normalization
    
    # Normalize gray image if it's a 32-bit float and convert to 8-bit for visualization
    # gray_normalized = cv2.normalize(grayImage, None, 0, 255, cv2.NORM_MINMAX)
    # gray_normalized = np.flip(grayImage, (0, 1))
    gray_normalized = cv2.convertScaleAbs(grayImage)

    depth_colored = cv2.applyColorMap(depth_normalized, cv2.COLORMAP_TURBO)

    # Convert grayscale to BGR (3-channel) to match the colored depth
    grayscale_bgr = cv2.cvtColor(gray_normalized, cv2.COLOR_GRAY2BGR)

    # Combine the grayscale and colored depth images with weighted alpha blending
    alpha = 0.9
    overlay = cv2.addWeighted(grayscale_bgr, alpha, depth_colored, 1 - alpha, 0)

    
    return overlay, grayscale_bgr, depth_colored

def show_overlay_noflip(grayImage, zImage):
    # Normalize the 32-bit depth image to a range of 0 to 255 for visualization
    depth_normalized = zImage
    depth_normalized = cv2.normalize(depth_normalized, None, 0, 255, cv2.NORM_MINMAX)
    depth_normalized = cv2.convertScaleAbs(depth_normalized)
    # depth_normalized = np.uint8(depth_normalized)  # Convert to 8-bit after normalization
    
    # Normalize gray image if it's a 32-bit float and convert to 8-bit for visualization
    # gray_normalized = cv2.normalize(grayImage, None, 0, 255, cv2.NORM_MINMAX)
    gray_normalized = cv2.convertScaleAbs(grayImage)

    depth_colored = cv2.applyColorMap(depth_normalized, cv2.COLORMAP_TURBO)

    # Convert grayscale to BGR (3-channel) to match the colored depth
    grayscale_bgr = cv2.cvtColor(gray_normalized, cv2.COLOR_GRAY2BGR)

    # Combine the grayscale and colored depth images with weighted alpha blending
    alpha = 0.9
    overlay = cv2.addWeighted(grayscale_bgr, alpha, depth_colored, 1 - alpha, 0)

    
    return overlay, grayscale_bgr, depth_colored


def show_overlay1(grayImage):

    # gray_normalized = np.flip(grayImage, (0, 1))

    grayscale_bgr = cv2.cvtColor(grayImage, cv2.COLOR_GRAY2BGR)

    
    return grayscale_bgr




