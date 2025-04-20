#include "arch/sys_arch.h"
#include "base/define.h"
#include "base/task/Mutex.h"

namespace
{
	class LwipSysArch
	{
	private:
		LwipSysArch() = default;

		base::task::Mutex _arch_protect_mutex{};

	public:
		static_function LwipSysArch &Instance()
		{
			static LwipSysArch o{};
			return o;
		}

		/// @brief 用于实现 sys_arch_protect
		void ArchProtect()
		{
			_arch_protect_mutex.Lock();
		}

		/// @brief 用于实现 sys_arch_unprotect
		void ArchUnprotect()
		{
			_arch_protect_mutex.Unlock();
		}
	};

} // namespace

PREINIT(LwipSysArch::Instance)

extern "C"
{
	sys_prot_t sys_arch_protect(void)
	{
		LwipSysArch::Instance().ArchProtect();
		return 1;
	}

	void sys_arch_unprotect(sys_prot_t pval)
	{
		LwipSysArch::Instance().ArchUnprotect();
	}
}
