#include <cassert>
#include <iostream>

#include "sql_query_builder.h"

int main() {
    SqlSelectQueryBuilder q1;
    q1.AddColumn("name").AddColumn("phone");
    q1.AddFrom("students");
    q1.AddWhere("id", "42").AddWhere("name", "John");
    assert(q1.BuildQuery() ==
        "SELECT name, phone FROM students WHERE id=42 AND name=John;");

    SqlSelectQueryBuilder q2;
    q2.AddColumns({ "name", "phone" }).AddFrom("students");
    assert(q2.BuildQuery() == "SELECT name, phone FROM students;");

    SqlSelectQueryBuilder q3;
    q3.AddColumn("id").AddColumns({ "name", "phone" }).AddFrom("students");
    assert(q3.BuildQuery() == "SELECT id, name, phone FROM students;");

    SqlSelectQueryBuilder q4;
    q4.AddFrom("students")
        .AddWhere(std::map<std::string, std::string>{{"id", "42"}, { "name", "John" }});
    assert(q4.BuildQuery() == "SELECT * FROM students WHERE id=42 AND name=John;");

    SqlSelectQueryBuilder q5;
    q5.AddWhere("age", "20")
        .AddWhere({ {"id", "42"}, {"name", "John"} })
        .AddColumns({ "name", "phone" })
        .AddFrom("students");
    assert(q5.BuildQuery() ==
        "SELECT name, phone FROM students WHERE age=20 AND id=42 AND name=John;");

    SqlSelectQueryBuilder q6;
    q6.AddColumns({}).AddWhere(std::map<std::string, std::string>{}).AddFrom("t");
    assert(q6.BuildQuery() == "SELECT * FROM t;");

    std::cout << q5.BuildQuery() << std::endl;
    std::cout << "All tests passed" << std::endl;
    return 0;
}