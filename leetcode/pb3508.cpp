#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Router {

    struct Packet {
        int source;
        int dest;
        int timestamp;
        Packet(int p_source = 0, int p_dest = 0, int p_timestamp = 0): source(p_source), dest(p_dest), timestamp(p_timestamp) {};

        bool operator==(const Packet& other) const {
            return source == other.source && dest == other.dest && timestamp == other.timestamp;
        }
    };

    struct PacketHasher {
        size_t operator()(const Packet* p) const {
            // Combine hashes of fields
            size_t h1 = std::hash<int>()(p->source);
            size_t h2 = std::hash<int>()(p->dest);
            size_t h3 = std::hash<int>()(p->timestamp);

            // Fowler–Noll–Vo or just XOR-shift combine
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    struct PacketEq {
        bool operator()(const Packet* a, const Packet* b) const {
            return *a == *b;
        }
    };


    deque<Packet*> packets;
    unordered_set<Packet*, PacketHasher, PacketEq> packet_set;
    unordered_map<int, deque<int>> counts; // Each dest -> vector<int> of timestamps
    
    int memoryLimit = 0;

    int lowerBound(deque<int>& v, int latest_timestamp) {
        return (int)(lower_bound(v.begin(), v.end(), latest_timestamp) - v.begin());
    }

    int upperBound(deque<int>& v, int latest_timestamp) {
        return (int)(upper_bound(v.begin(), v.end(), latest_timestamp) - v.begin());
    }

public:
    Router(int p_memoryLimit) {
        memoryLimit = p_memoryLimit;
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        Packet* packet = new Packet(source, destination, timestamp);
        if (packet_set.count(packet)) {
            delete packet;
            return false;
        }

        if (packets.size() == memoryLimit) {
            counts[packets.front()->dest].pop_front();
            packet_set.erase(packets.front());
            delete packets.front();
            packets.pop_front();
        }

        counts[destination].push_back(timestamp);
        packets.push_back(packet);
        packet_set.insert(packets.back());
        return true;
    }
    
    vector<int> forwardPacket() {
        vector<int> info;
        if (packets.size() != 0) {
            Packet* packet = packets.front();
            info.resize(3);
            info[0] = packet->source;
            info[1] = packet->dest;
            info[2] = packet->timestamp;
            counts[packet->dest].pop_front();
            packet_set.erase(packet);
            delete packet;
            packets.pop_front();
        }
        return info;
    }
    
    int getCount(int destination, int startTime, int endTime) {
        auto it = counts.find(destination);
        if (it == counts.end() || it->second.empty()) return 0;

        int left = lowerBound(it->second, startTime);
        int right = upperBound(it->second, endTime);

        return right - left;
    }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */