#pragma once

enum ComponentID {
	Transform,
	Velocity,
	DrawRect
};

namespace Components {
	struct Transform {
		int x;
		int y;
	};

	struct Velocity {
		int x;
		int y;
	};

	struct DrawRect {
		int w;
		int h;
		int r;
		int g;
		int b;
	};
}