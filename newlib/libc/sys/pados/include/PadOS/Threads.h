
typedef struct PThreadControlBlock
{
    uint32_t    TLSSlotCount;
    void**      TLSSlots;
} PThreadControlBlock;

extern PThreadControlBlock* current_thread_control_block;
