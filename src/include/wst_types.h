#pragma once

#include <vector>
#include <memory>
#include <string>

using namespace std;

namespace wst {

    enum FillScene {
        FillScene_No = 0,
        FillScene_Repeat_x,
        FillScene_Repeat_y,
        FillScene_Repeat_xy,
        FillScene_Stretch_x,
        FillScene_Stretch_y,
        FillScene_Stretch_xy
    };

    struct Size {
        Size(int w, int h) { this->w = w; this->h = h; }
        Size() { this->w = 0; this->h = 0; }

        Size operator+ (const Size& other) const { return Size(w + other.w, h + other.h); }
        Size operator- (const Size& other) const { return Size(w - other.w, h - other.h); }
        Size operator* (const Size& other) const { return Size(w * other.w, h * other.h); }
        Size operator/ (const Size& other) const { return Size(w / other.w, h / other.h); }

        Size operator+ (int val) const { return Size(w + val, h + val); }
        Size operator- (int val) const { return Size(w - val, h - val); }
        Size operator* (int val) const { return Size(w * val, h * val); }
        Size operator/ (int val) const { return Size(w / val, h / val); }

        Size& operator+= (int val) { w += val; h += val; return *this; }
        Size& operator-= (int val) { w -= val; h -= val; return *this; }
        Size& operator*= (int val) { w *= val; h *= val; return *this; }
        Size& operator/= (int val) { w /= val; h /= val; return *this; }

        int w, h;
    };

    struct Pos {
        Pos(int x, int y) { this->x = x; this->y = y; }
        Pos() { x = 0; y = 0; }

        Pos operator+ (const Pos& other) const { return Pos(x + other.x, y + other.y); }
        Pos operator- (const Pos& other) const { return Pos(x - other.x, y - other.y); }
        Pos operator* (const Pos& other) const { return Pos(x * other.x, y * other.y); }
        Pos operator/ (const Pos& other) const { return Pos(x / other.x, y / other.y); }

        Pos& operator+= (const Pos& other) { x += other.x; y += other.y; return *this; }
        Pos& operator-= (const Pos& other) { x -= other.x; y -= other.y; return *this; }
        Pos& operator*= (const Pos& other) { x *= other.x; y *= other.y; return *this; }
        Pos& operator/= (const Pos& other) { x /= other.x; y /= other.y; return *this; }


        Pos operator+ (int val) const { return Pos(x + val, y + val); }
        Pos operator- (int val) const { return Pos(x - val, y - val); }
        Pos operator* (int val) const { return Pos(x * val, y * val); }
        Pos operator/ (int val) const { return Pos(x / val, y / val); }

        Pos operator+= (int val) { x += val; y += val; return *this; }
        Pos operator-= (int val) { x -= val; y -= val; return *this; }
        Pos operator*= (int val) { x *= val; y *= val; return *this; }
        Pos operator/= (int val) { x /= val; y /= val; return *this; }

        int x; // negative is left, positive is right
        int y; // negative is down, positive is up
    };

    struct Rect {
        Rect() { topleft.x = 0; topleft.y = 0; size.w = 0; size.h = 0; }
        Rect(int left, int top, int width, int height) {
            topleft.x = left;
            topleft.y = top;
            size.w = width;
            size.h = height;
        }

        Rect operator+ (const Pos& other) const { return Rect(topleft.x + other.x, topleft.y + other.x, size.w, size.h); }
        Rect operator- (const Pos& other) const { return Rect(topleft.x - other.x, topleft.y - other.x, size.w, size.h); }
        Rect operator* (const Pos& other) const { return Rect(topleft.x * other.x, topleft.y * other.x, size.w, size.h); }
        Rect operator/ (const Pos& other) const { return Rect(topleft.x / other.x, topleft.y / other.x, size.w, size.h); }
        
        Rect& operator+= (int val) { topleft.x += val; topleft.y += val; return *this; }
        Rect& operator-= (int val) { topleft.x -= val; topleft.y -= val; return *this; }
        Rect& operator*= (int val) { topleft.x *= val; topleft.y *= val; return *this; }
        Rect& operator/= (int val) { topleft.x /= val; topleft.y /= val; return *this; }

        Pos topleft;
        Size size;

    };

    struct Pos_graph_node {
        Pos_graph_node(Pos_graph_node const&) = delete;
        Pos_graph_node& operator=(Pos_graph_node const&) = delete;

        static shared_ptr<Pos_graph_node> root()
        {
            static shared_ptr<Pos_graph_node> s{ new Pos_graph_node };
            return s;
        }


        Pos_graph_node() {
            _fill_property = FillScene_No;
            _pos = Pos(0,0);
            _size = Size(0,0);
            _abs_pos = Pos(0,0);
        }

        virtual Size size() { return _size; }
        virtual void set_size(Size s) { _size = s; }

        virtual Pos pos() { return _pos; }
        virtual void set_pos(Pos pos) { _pos = pos; }
        
        virtual Pos abs_pos() { 
            return _abs_pos;
        }

        void calc_abs_pos_tree(Pos parent_pos) {
            for (auto c : _children) {
                Pos p = c->calc_abs_pos(parent_pos);
                calc_abs_pos_tree(p);
            }
        }

        void update(Pos parent_pos, Size parent_size) {
            if (_fill_property == FillScene_Repeat_x) {
                Size target_size = Size(parent_size.w, 0) + _orig_size;

                set_size(target_size);
            }

            for (auto c : _children) {
                c->update(_abs_pos, _size);
            }
        }

        void set_fill(FillScene prop) {
            _fill_property = prop;
        }

        FillScene get_fill() { return _fill_property; }

        
        static shared_ptr<Pos_graph_node> find_parent(shared_ptr<Pos_graph_node> node, shared_ptr<Pos_graph_node> parent) {
            
            for (auto c : parent->_children) {
                if (c == node) {
                    return parent;
                }

                auto p = find_parent(node, c);

                if (p != nullptr) {
                    return p;
                }
            }

            return nullptr;
        }
        
        void add(shared_ptr<Pos_graph_node> node) {
            _children.push_back(node);
        }

        void remove(shared_ptr<Pos_graph_node> node) {
            for (size_t i = 0; i < _children.size(); ++i) {
                if (_children[i] == node) {
                    _children.erase(_children.begin() + i, _children.begin() + i + 1);
                    return;
                }
            }
        }

        void remove_all() {
            while (!_children.empty()) { _children.pop_back(); }
        }

    private:
        

    protected:
        Pos calc_abs_pos(Pos parent_abs_pos) {
            Pos p = _pos;

            p += parent_abs_pos;
            _abs_pos = p;
            return p;
        }

        Pos     _pos;
        Pos     _abs_pos;
        Pos     _parent_abs_pos;
        Pos     _parent_size;
        Size    _size;
        Size    _orig_size;
        FillScene _fill_property;
        
        vector<shared_ptr<Pos_graph_node>> _children;
    };
}