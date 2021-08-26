#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string.h>
#include <string>
#include <assert.h>
#include <mutex>

static int MY_SYS_MemAlloc(uint64_t *pphyaddr, void **pviraddr, uint32_t size) {
    *pviraddr = new char[size];
    *pphyaddr = (uint64_t)*pviraddr;
    return 0;
}

static int MY_SYS_MemFree(uint64_t pphyaddr, void *pviraddr) {
    char *buf = (char*)pviraddr;
    delete []buf;
    return 0;
}

struct Buffer {
    Buffer() {}
    Buffer(uint32_t s) {
        ensure_size(s);
    }
    ~Buffer() {
        destroy();
    }
    void ensure_size(uint32_t s) {
        if (s > size) {
            destroy();
        }
        assert(0 == MY_SYS_MemAlloc((uint64_t*)&phy, (void**)&vir, s));
        size = s;
    }
    void destroy() {
        if (vir != nullptr && phy != nullptr) {
            MY_SYS_MemFree((uint64_t)phy, (void*)vir);
            vir = nullptr;
            phy = nullptr;
            size = 0;
        }
    }
    uint8_t *vir = nullptr;
    uint8_t *phy = nullptr;
    uint32_t size = 0;
};

class BufferPool {
public:
    ~BufferPool() {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (!m_buffers.empty()) {
            for (auto &buf : m_buffers) {
                delete buf;
            }
            m_buffers.clear();
        }
    }

    std::shared_ptr<Buffer> pop(uint32_t s) {
        std::lock_guard<std::mutex> lg(m_mutex);
        Buffer *buf = nullptr;
        if (m_buffers.empty()) {
            buf = new Buffer(s);
        } else {
            for (auto itr = m_buffers.begin(); itr != m_buffers.end(); ++itr) {
                if ((*itr)->size >= s) {
                    buf = *itr;
                    m_buffers.erase(itr);
                    break;
                }
            }
        }
        if (buf == nullptr) {
            buf = m_buffers.back();
            m_buffers.pop_back();
            buf->ensure_size(s);
        }
        return std::shared_ptr<Buffer>(buf, [this](void *ptr)->void { this->push((Buffer*)ptr); });
    }

private:
    void push(Buffer *buf) {
        if (buf == nullptr) {
            return;
        }
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_buffers.size() < m_capacity) {
            m_buffers.push_back(buf);
        } else {
            delete buf;
        }
    }

private:
    std::mutex m_mutex;
    size_t m_capacity;
    std::vector<Buffer*> m_buffers;
};


int main() {
    BufferPool buffer_pool;
    auto buffer_1 = buffer_pool.pop(100);
    return 0;
}