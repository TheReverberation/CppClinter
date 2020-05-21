//
// Created by Daniil Nedaiborsch on 27.04.2020.
//

#include "Linter.hpp"


using std::max;
using std::string;
using std::vector;
using std::shared_ptr;
using clnt::states::Statement;

namespace {
    vector<pair<StatementType, string>>
    groupExpressions(Slice<vector<shared_ptr<Statement>>> const& statements) {
        vector<pair<StatementType, string>> groups;
        for (size_t i = 0; i < statements.size();) {
            if (statements[i]->type == StatementType::INSTRUCTION ||
                statements[i]->type == StatementType::STRUCT ||
                statements[i]->type == StatementType::IF || 
                statements[i]->type == StatementType::ELSE || 
                statements[i]->type == StatementType::IFELSE ||
                statements[i]->type == StatementType::PREPROCESSOR) {
                groups.push_back({statements[i]->type, statements[i]->linted()});
                ++i;
            } else if (statements[i]->type == StatementType::EXPRESSION && statements[i]->linted() == "\n") {
                groups.push_back({statements[i]->type, statements[i]->linted()});
                ++i;
            } else {
                auto groupEnd = std::find_if(statements.begin() + i, statements.end(),
                        [] (shared_ptr<Statement> const& s) -> bool {
                    return s->type == StatementType::BLOCK ||
                           s->type == StatementType::INSTRUCTION ||
                           s->type == StatementType::STRUCT;
                });

                assert(groupEnd != statements.end());

                if (groupEnd != statements.end()) {
                    ++groupEnd;
                }

                string accumulated = "";
                for (auto s = statements.begin() + i; s != groupEnd; ++s) {
                    if ((*s)->linted() != "\n") {
                        accumulated += (*s)->linted() + " ";
                    }
                }
                
                groups.push_back({(*(groupEnd - 1))->type, accumulated});
                i = groupEnd - statements.begin();
            }
        }
        return groups;
    }

    string joinGlobalStatements(vector<pair<StatementType, string>> const& statements) {
        vector<string> joinedLines;
        for (size_t i = 0; i < statements.size(); ++i)  {
            if (statements[i].second == "\n") {
                joinedLines.emplace_back("\n");
            } else {
                int margin = 0;
                if (statements[i].first == StatementType::STRUCT || statements[i].first == StatementType::BLOCK) {
                    margin = 3;
                } else {
                    margin = 1;
                }
                
                int emptyStrBefore = 0;
                for (int j = joinedLines.size() - 1; j >= 0 && (joinedLines[j] == "\n"); --j) {
                    ++emptyStrBefore;
                }

                // if it's not the first line
                if (i != 0) {
                    for (size_t j = 0; j < max(0, margin - emptyStrBefore); ++j) {
                        joinedLines.emplace_back("\n");
                    }
                }

                joinedLines.push_back(statements[i].second);
            }
        }
        return clnt::accumulate(joinedLines.begin(), joinedLines.end(), string()); 
    }

    string joinStatements(vector<pair<StatementType, string>> const& statements) {
        std::cout << "joinStatements:\n";
        string joined = "";
        for (size_t i = 0; i < statements.size(); ++i) {
            auto state = statements[i];
            std::cout << "linted: " << state.second << '\n';
            joined += state.second;
            if (state.second != "\n" && i + 1 < statements.size() && statements[i + 1].second != "\n") {
                joined += "\n";
            }
        }
        std::cout << "joined: " << joined << '\n';
        return joined;
    }
}

namespace clnt::lint {

    Linter::Linter() {}


    string Linter::lint(Slice<vector<shared_ptr<Statement>>> const& statements, Space space) {
        for (auto& now : statements) {
            now->lint();
        }
        vector<pair<StatementType, string>> groups = ::groupExpressions(statements);
        if (space == Space::GLOBAL) {
            return ::joinGlobalStatements(groups);
        } else {
            return ::joinStatements(groups);
        }
    }
}
