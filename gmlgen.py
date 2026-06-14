import os
import re
import chardet

def safe_read(path):
    """自动检测文件编码并安全读取"""
    with open(path, "rb") as f:
        raw = f.read()
    enc = chardet.detect(raw)["encoding"] or "utf-8"
    return raw.decode(enc, errors="ignore")

code_out = "/* THIS FILE IS GENERATED - DO NOT EDIT BY HAND! */\n\n"

for root, dirs, files in os.walk("./cpp/src/"):
    for fname in files:
        if not fname.endswith(".cpp"):
            continue
        fpath = os.path.join(root, fname)
        code_in = safe_read(fpath)

        # 匹配 GM_EXPORT 函数定义
        for docs, typename, name, param_str in re.findall(
            r"((?:///[^\n]*\n)+)?GM_EXPORT (\w+) (\w+)\(([^\)]*)\)", code_in
        ):
            if param_str:
                param_split = param_str.split(", ")
            else:
                param_split = []

            params = [tuple(p.split(" ")) for p in param_split if " " in p]
            param_str_names = ", ".join([p[1] for p in params])
            param_str_types = ", ".join([p[0] for p in params])

            code_out += f"{docs or ''}function {name}({param_str_names})\n"
            code_out += "{\n"
            code_out += '\tgml_pragma("forceinline");\n'
            code_out += '\tstatic _fn = external_define(\n'
            code_out += f'\t\tGMD3D11_PATH, "{name}", dll_cdecl, {typename},\n'

            if len(params) > 0:
                code_out += f'\t\t{len(params)}, {param_str_types});\n'
                code_out += f'\treturn external_call(_fn, {param_str_names});\n'
            else:
                code_out += '\t\t0);\n'
                code_out += '\treturn external_call(_fn);\n'

            code_out += "}\n\n"

code_out = code_out.rstrip() + "\n"

# 输出时也指定 UTF-8
os.makedirs("./scripts/__d3d11_generated", exist_ok=True)
with open("./scripts/__d3d11_generated/__d3d11_generated.gml", "w", encoding="utf-8") as f:
    f.write(code_out)

print("GML generated!")
