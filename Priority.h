#pragma once
#include "Node.h"

class Priority {
public:
	bool operator ()( const std::shared_ptr<Node> left, const std::shared_ptr<Node> right)const;
};

