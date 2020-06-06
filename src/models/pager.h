#ifndef SPOTIFY_PLUSPLUS_PAGER_H
#define SPOTIFY_PLUSPLUS_PAGER_H

#include <string>
#include <vector>

#include <nlohmann/json.hpp>
namespace spotify {
    template<class T>
    class Pager {
     public:
        Pager<T>();
        explicit Pager<T>(nlohmann::json pagerJson);

        [[nodiscard]] const std::string& getHref() const;
        [[nodiscard]] const std::vector<T>& getItems() const;
        [[nodiscard]] int getLimit() const;
        [[nodiscard]] const std::string& getNext() const;
        [[nodiscard]] int getOffset() const;
        [[nodiscard]] const std::string& getPrevious() const;
        [[nodiscard]] int getTotal() const;

     private:
        std::string href;
        std::vector<T> items;
        int limit;
        std::string next;
        int offset;
        std::string previous;
        int total;
    };

    template<typename T>
    Pager<T>::Pager() = default;

    template<typename T>
    Pager<T>::Pager(nlohmann::json pagerJson) {
        if (!pagerJson["href"].is_null())
            href = pagerJson["href"];
        for (const auto& json : pagerJson["items"])
            items.push_back(T(json));
        if (!pagerJson["limit"].is_null())
            limit = pagerJson["limit"];
        if (!pagerJson["next"].is_null())
            next = pagerJson["next"];
        if (!pagerJson["offset"].is_null())
            offset = pagerJson["offset"];
        if (!pagerJson["previous"].is_null())
            previous = pagerJson["previous"];
        total = pagerJson["total"];
    }

    template<typename T>
    const std::string& Pager<T>::getHref() const {
        return href;
    }

    template<typename T>
    const std::vector<T>& Pager<T>::getItems() const {
        return items;
    }

    template<typename T>
    int Pager<T>::getLimit() const {
        return limit;
    }

    template<typename T>
    const std::string& Pager<T>::getNext() const {
        return next;
    }

    template<typename T>
    int Pager<T>::getOffset() const {
        return offset;
    }

    template<typename T>
    const std::string& Pager<T>::getPrevious() const {
        return previous;
    }

    template<typename T>
    int Pager<T>::getTotal() const {
        return total;
    }
}  // namespace spotify
#endif
