#pragma once
#include <map>
#include <string>
#include <utility>
#include <vector>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column);
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;

    SqlSelectQueryBuilder& AddFrom(const std::string& table);

    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value);
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;

    std::string BuildQuery() const;

private:
    std::vector<std::string> columns_;
    std::string table_;
    std::vector<std::pair<std::string, std::string>> where_;
};