#ifndef SPOTIFY_PLUSPLUS_CURSORPAGER_H
#define SPOTIFY_PLUSPLUS_CURSORPAGER_H

#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Cursor.h"

template<class T>
class CursorPager {
 public:
    CursorPager<T>();
    explicit CursorPager<T>(nlohmann::json pagerJson);

    [[nodiscard]] const std::string& getHref() const;
    [[nodiscard]] const std::vector<T>& getItems() const;
    [[nodiscard]] int getLimit() const;
    [[nodiscard]] const std::string& getNext() const;
    [[nodiscard]] std::shared_ptr<Cursor> getCursors() const;
    [[nodiscard]] int getTotal() const;

 private:
    std::string href;
    std::vector<T> items;
    int limit;
    std::string next;
    std::shared_ptr<Cursor> cursors;
    int total;
};

template<typename T>
CursorPager<T>::CursorPager() = default;

template<typename T>
CursorPager<T>::CursorPager(nlohmann::json pagerJson) {
    href = pagerJson["href"];
    for (nlohmann::json json : pagerJson["items"])
        items.push_back(T(json));
    limit = pagerJson["limit"];
    if (!pagerJson["next"].is_null())
        next = pagerJson["next"];
    cursors = std::make_shared<Cursor>(pagerJson["cursors"]);
    total = pagerJson["total"];
}

template<typename T>
const std::string& CursorPager<T>::getHref() const {
    return href;
}

template<typename T>
const std::vector<T>& CursorPager<T>::getItems() const {
    return items;
}

template<typename T>
int CursorPager<T>::getLimit() const {
    return limit;
}

template<typename T>
const std::string& CursorPager<T>::getNext() const {
    return next;
}

template<typename T>
std::shared_ptr<Cursor> CursorPager<T>::getCursors() const {
    return cursors;
}

template<typename T>
int CursorPager<T>::getTotal() const {
    return total;
}

#endif
