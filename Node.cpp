#include "Node.h"

bool Node::operator <(const Node& other) const { return freq < other.freq; }
int Node::get_frequency()const { return freq; }
void  Node::set_frequency(int value) {
	freq = value;
}
std::string Node::get_code() const { return code_string; }
void Node::set_code(const std::string& information) {
	code_string = information;
}
uch_type Node::get_byte() const { return ch; }
bool Node::is_leaf()const {
	return (left == nullptr && right == nullptr);
}
