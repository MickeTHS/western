#pragma once

#include <vector>

namespace wst {

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
        Pos_graph_node() {
            _parent = NULL;
            _pos = Pos(0,0);
            _size = Size(0,0);
        }

        virtual Size size() { return _size; }
        virtual void set_size(Size s) { _size = s; }

        virtual Pos pos() { return _pos; }
        virtual void set_pos(Pos pos) { _pos = pos; }
        
        virtual Pos abs_pos() { 
            return calc_abs_pos();
        }
        
        void set_parent(Pos_graph_node* node) { _parent = node; }
        Pos_graph_node* parent() { return _parent; }

        void add(Pos_graph_node* node) {
            _children.push_back(node);
        }

        void remove(Pos_graph_node* node) {
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
        Pos calc_abs_pos() const {
            Pos p = _pos;

            if (_parent != NULL) {
                p += _parent->calc_abs_pos();
            }

            return p;
        }

        Pos     _pos;
        Size    _size;
        
        std::vector<Pos_graph_node*> _children;
        Pos_graph_node  *_parent;
    };
}