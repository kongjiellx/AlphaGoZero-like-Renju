#ifndef CPP_BOARD_H
#define CPP_BOARD_H

#include <vector>
#include <tuple>
#include "conf/conf.pb.h"
#include <google/protobuf/text_format.h>
#include "cpp/src/data_structure/data_structure.h"
#include "conf/conf_cc_proto_pb/conf/conf.pb.h"

class Stone {
public:
    int x;
    int y;
    Player player;

    Stone(int x, int y, Player player): x(x), y(y), player(player) {}

};

class Board {
private:
    int size;
    int win_num;
    std::vector<int> illegal_idx;
    std::vector<int> legal_idx;
    std::tuple<int, int> last_pos;
    BOARD_STATUS board_status;

    void do_turn();

    bool is_legal(const Stone &stone);

    void add_stone(const Stone &stone);

    std::tuple<bool, Player> check_done(const Stone &stone);

    int count_on_direction(const Stone &stone, int xdirection, int ydirection, int num);

public:
    Player current_player;

    const BOARD_STATUS &get_current_status();

    Board(const conf::GameConf &conf);

    std::tuple<bool, Player> step(const Stone &stone);

    std::string to_str();

    const std::vector<int> &get_illegal_idx() const;

    const std::vector<int> &get_legal_idx() const;

    int get_size() const;

    const std::tuple<int, int> &get_last_pos() const;
};


#endif //CPP_BOARD_H
