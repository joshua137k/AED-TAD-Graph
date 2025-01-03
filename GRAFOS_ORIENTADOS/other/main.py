import os

# Caminho da pasta onde estão os arquivos
folder_path = "other"

# Lista todos os arquivos .txt na pasta
txt_files = [file for file in os.listdir(folder_path) if file.endswith(".txt")]
print(len(txt_files))
#for txt_file in txt_files:
 #   print('"GRAFOS_ORIENTADOS/other/'+txt_file+'",')
