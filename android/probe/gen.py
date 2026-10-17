import json, os
ts = json.load(open('android/probe/tests.json'))
os.makedirs('android/probe/src', exist_ok=True)
manifest = []
for t in ts:
    if t['idx'] == 19:      # 依赖已安装的 readline，跳过（我们用 bundled）
        continue
    open(f"android/probe/src/probe_{t['idx']:02d}.c", 'w').write(t['prog'] + "\n")
    manifest.append(t)
json.dump(manifest, open('android/probe/manifest.json', 'w'), indent=1)
print(f"generated {len(manifest)} probes")
