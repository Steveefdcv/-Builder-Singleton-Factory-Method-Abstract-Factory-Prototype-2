#include "sql_query_builder.h"

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& column) {
    columns_.push_back(column);
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(
    const std::vector<std::string>& columns) noexcept {
    columns_.insert(columns_.end(), columns.begin(), columns.end());
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& table) {
    table_ = table;
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& key,
    const std::string& value) {
    where_.emplace_back(key, value);
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(
    const std::map<std::string, std::string>& kv) noexcept {
    where_.insert(where_.end(), kv.begin(), kv.end());
    return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() const {
    std::string query = "SELECT ";

    if (columns_.empty()) {
        query += "*";
    }
    else {
        for (size_t i = 0; i < columns_.size(); ++i) {
            if (i > 0) query += ", ";
            query += columns_[i];
        }
    }

    query += " FROM " + table_;

    if (!where_.empty()) {
        query += " WHERE ";
        for (size_t i = 0; i < where_.size(); ++i) {
            if (i > 0) query += " AND ";
            query += where_[i].first + "=" + where_[i].second;
        }
    }

    query += ";";
    return query;
}