/********************************************************************************
 * @author: TURIING
 * @email: turiing@163.com
 * @date: 2025/3/30 21:05
 * @version: 1.0
 * @description:
 ********************************************************************************/
#ifndef COMMON_H
#define COMMON_H

// #include "LogManager.h"
#include <functional>

/************************************************* Marco ************************************************************/
#define BIT(x) (1 << (x))

/************************************************* Type *************************************************************/
struct Size {
	uint32_t width	= 0;
	uint32_t height = 0;
};

enum class MouseButton {
	None   = 0,
	Left   = BIT(0),
	Right  = BIT(1),
	Middle = BIT(2),
};

struct Point {
	int x = 0;
	int y = 0;
};

constexpr Size         WINDOW_SIZE = {1000, 800};
inline constexpr float FRAME_TIME  = 1 / 60.0; // 每秒里每帧的耗时

#endif // COMMON_H
