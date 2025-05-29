Import("env")

def before_upload(source, target, env):
    print("Otomatik olarak LittleFS dosyaları yükleniyor...")
    env.Execute("pio run --target uploadfs")

env.AddPreAction("upload", before_upload)
