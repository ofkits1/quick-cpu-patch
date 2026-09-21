#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <intrin.h>

#pragma comment(linker, "/NODEFAULTLIB")
#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/export:SL_AllocBuffer=stlib_orig.SL_AllocBuffer")
#pragma comment(linker, "/export:SL_FreeBuffer=stlib_orig.SL_FreeBuffer")
#pragma comment(linker, "/export:SL_QueryAllCapabilities=stlib_orig.SL_QueryAllCapabilities")
#pragma comment(linker, "/export:SL_QueryCapabilities=stlib_orig.SL_QueryCapabilities")
#pragma comment(linker, "/export:SL_Run_AVX=stlib_orig.SL_Run_AVX")
#pragma comment(linker, "/export:SL_Run_AVX2=stlib_orig.SL_Run_AVX2")
#pragma comment(linker, "/export:SL_Run_AVX512=stlib_orig.SL_Run_AVX512")
#pragma comment(linker, "/export:SL_Run_Generic=stlib_orig.SL_Run_Generic")
#pragma comment(linker, "/export:SL_Run_SSE2=stlib_orig.SL_Run_SSE2")
#pragma function(memcpy, memset, memcmp)

#define HM_QUICKCPU 0xB3571CE0u

typedef struct {
    unsigned rva;
    unsigned char old[8];
    unsigned char new_[8];
    unsigned n;
} QC_PATCH;

static const QC_PATCH kPatches[] = {
    {0x0001FF0Cu, {0x1B, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x04, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 2u},
    {0x00020048u, {0x1B, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x04, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 2u},
    {0x00020190u, {0x13, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x04, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 2u},
    {0x00020B98u, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x00020B9Cu, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x00029CF8u, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x00029CFCu, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x00029F0Bu, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x00029F0Fu, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x0002A09Cu, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x0002A0A0u, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x0004BFC1u, {0x28, 0x47, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x0004BFC5u, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x000509B1u, {0x28, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x17, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 2u},
    {0x000509C5u, {0x02, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x17, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 2u},
    {0x00050A01u, {0x30, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x17, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 2u},
    {0x0008FCA0u, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x0008FCA4u, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x0009D877u, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x0009D87Bu, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x0009D9A0u, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x0009D9A4u, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x000A53D6u, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x000A53DAu, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
    {0x000F8589u, {0x28, 0x48, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 3u},
    {0x000F858Du, {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1u},
};

static HMODULE g_orig;
static volatile LONG g_done;

void *memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    while (n--)
        *d++ = *s++;
    return dst;
}

void *memset(void *dst, int c, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    while (n--)
        *d++ = (unsigned char)c;
    return dst;
}

int memcmp(const void *a, const void *b, size_t n)
{
    const unsigned char *p = (const unsigned char *)a;
    const unsigned char *q = (const unsigned char *)b;
    while (n--) {
        if (*p != *q)
            return (int)*p - (int)*q;
        p++;
        q++;
    }
    return 0;
}

static unsigned hmix(unsigned h, unsigned char b)
{
    h ^= (unsigned)b;
    h = ((h << 7) | (h >> 25)) + 0x6D2B79F5u;
    h ^= h >> 11;
    return h;
}

static unsigned h_wfnv(const wchar_t *s, unsigned nbytes)
{
    unsigned h = 0xA5A5C3E1u;
    unsigned n, i;
    if (!s || nbytes < 2)
        return 0;
    n = nbytes / 2u;
    for (i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)(s[i] & 0xFF);
        if (c >= 'A' && c <= 'Z')
            c = (unsigned char)(c + 32);
        h = hmix(h, c);
    }
    return h;
}

typedef struct _USTR {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} USTR;

typedef struct _LDR {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    USTR FullDllName;
    USTR BaseDllName;
} LDR;

typedef struct _PEB_LDR {
    ULONG Length;
    UCHAR Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
} PEB_LDR;

typedef struct _PEB {
    UCHAR Reserved1[2];
    UCHAR BeingDebugged;
    UCHAR Reserved2[1];
    PVOID Reserved3[2];
    PEB_LDR *Ldr;
} PEB;

static void *peb_ptr(void)
{
    return (void *)__readgsqword(0x60);
}

static unsigned host_exe_hash(void)
{
    PEB *peb = (PEB *)peb_ptr();
    LIST_ENTRY *head, *cur;
    LDR *e;
    if (!peb || !peb->Ldr)
        return 0;
    head = &peb->Ldr->InLoadOrderModuleList;
    cur = head->Flink;
    if (!cur || cur == head)
        return 0;
    e = (LDR *)cur;
    if (!e->BaseDllName.Buffer || e->BaseDllName.Length < 4)
        return 0;
    return h_wfnv(e->BaseDllName.Buffer, e->BaseDllName.Length);
}

static BYTE *host_base(void)
{
    PEB *peb = (PEB *)peb_ptr();
    if (peb && peb->Ldr) {
        LIST_ENTRY *head = &peb->Ldr->InLoadOrderModuleList;
        LIST_ENTRY *cur = head->Flink;
        if (cur && cur != head) {
            LDR *e = (LDR *)cur;
            if (e->DllBase)
                return (BYTE *)e->DllBase;
        }
    }
    return 0;
}

static int patch_bytes(BYTE *dst, const unsigned char *old, const unsigned char *new_, unsigned n)
{
    DWORD old_prot, tmp;
    if (!dst || !old || !new_ || !n)
        return 0;
    if (memcmp(dst, old, n) != 0 && memcmp(dst, new_, n) != 0)
        return 0;
    if (memcmp(dst, new_, n) == 0)
        return 1;
    if (!VirtualProtect(dst, n, PAGE_EXECUTE_READWRITE, &old_prot))
        return 0;
    memcpy(dst, new_, n);
    VirtualProtect(dst, n, old_prot, &tmp);
    FlushInstructionCache(GetCurrentProcess(), dst, n);
    return 1;
}

static void apply_unlock(void)
{
    BYTE *base;
    unsigned i, ok, need;

    if (g_done)
        return;
    if (host_exe_hash() != HM_QUICKCPU)
        return;
    base = host_base();
    if (!base)
        return;
    ok = 0;
    need = (unsigned)(sizeof(kPatches) / sizeof(kPatches[0]));
    for (i = 0; i < need; ++i) {
        const QC_PATCH *p = &kPatches[i];
        if (patch_bytes(base + p->rva, p->old, p->new_, p->n))
            ok++;
    }
    if (ok == need)
        InterlockedExchange(&g_done, 1);
}

static DWORD WINAPI apply_later(LPVOID p)
{
    unsigned n = 0;
    (void)p;
    for (;;) {
        apply_unlock();
        if (g_done || ++n >= 120u)
            break;
        Sleep(50u);
    }
    return 0;
}

static wchar_t *find_last_slash(wchar_t *s)
{
    wchar_t *last = NULL;
    while (s && *s) {
        if (*s == L'\\')
            last = s;
        s++;
    }
    return last;
}

BOOL WINAPI DllMain(HINSTANCE h, DWORD reason, LPVOID reserved)
{
    wchar_t path[MAX_PATH];
    (void)reserved;
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(h);
        if (GetModuleFileNameW(h, path, MAX_PATH)) {
            lstrcpyW(find_last_slash(path) + 1, L"stlib_orig.dll");
            g_orig = LoadLibraryW(path);
        }
        apply_unlock();
        if (!g_done)
            QueueUserWorkItem(apply_later, 0, WT_EXECUTELONGFUNCTION);
    } else if (reason == DLL_PROCESS_DETACH && g_orig) {
        FreeLibrary(g_orig);
        g_orig = NULL;
    }
    return TRUE;
}
