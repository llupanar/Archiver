#pragma once

#include <iostream>

using uch_type = unsigned char;
class Node
{
public:
	Node() = default;
	std::shared_ptr<Node> left{ nullptr };
	std::shared_ptr<Node> right{ nullptr };
	std::shared_ptr<Node> parent{ nullptr };
	Node(uch_type uch, int f) : ch(uch), freq(f) {}
	bool operator <(const Node& other)const;
	int get_frequency()const;
	void set_frequency(int value);
	std::string get_code() const;
	void set_code(const std::string& information);
	uch_type get_byte() const;
	bool is_leaf()const;
private:
	uch_type ch{ 0 };
	int freq{ 0 };
	std::string code_string{ "" };
};
