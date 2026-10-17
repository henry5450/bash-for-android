import re, os, json, sys

src = open('aclocal.m4').read()
# 匹配 AC_RUN_IFELSE([AC_LANG_SOURCE([[ ... ]])], [YES], [NO],\n [DEFAULT])
pat = re.compile(
    r'AC_RUN_IFELSE\(\[AC_LANG_SOURCE\(\[\[\n(.*?)\n\]\]\)\],\s*\[(.*?)\],\s*\[(.*?)\],\s*\[(.*?)\]\s*\)',
    re.S)
out = []
for i, m in enumerate(pat.finditer(src)):
    prog, yes, no, dflt = m.group(1), m.group(2).strip(), m.group(3).strip(), m.group(4).strip()
    out.append(dict(idx=i, prog=prog, yes=yes, no=no, dflt=dflt))
json.dump(out, open('android/probe/tests.json','w'), indent=1)
print(f"extracted {len(out)} run-tests\n")
for t in out:
    # 从 yes/no 里提取变量名
    names = set(re.findall(r'(bash_cv_\w+)', t['yes'] + t['no'] + t['dflt']))
    print(f"[{t['idx']:2d}] var={','.join(sorted(names)) or '??'}")
    print(f"     yes  = {t['yes'][:70]}")
    print(f"     no   = {t['no'][:70]}")
    print(f"     dflt = {t['dflt'][:100]}")
