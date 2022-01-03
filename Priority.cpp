#include "Priority.h"
bool Priority:: operator ()(const std::shared_ptr<Node> left, const std::shared_ptr<Node> right)const {
	return left->get_frequency() > right->get_frequency();
}