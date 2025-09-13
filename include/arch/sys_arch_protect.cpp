#include "arch/sys_arch.h"
#include "base/SingletonProvider.h"
#include "base/task/Mutex.h"

namespace
{
	class LwipSysArch
	{
	private:
		base::task::Mutex _arch_protect_mutex{};

	public:
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

	base::SingletonProvider<LwipSysArch> _provider{};

} // namespace

extern "C"
{
	sys_prot_t sys_arch_protect(void)
	{
		_provider.Instance().ArchProtect();
		return 1;
	}

	void sys_arch_unprotect(sys_prot_t pval)
	{
		_provider.Instance().ArchUnprotect();
	}
}
