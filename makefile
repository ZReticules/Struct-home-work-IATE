# Автоматический Makefile (GCC / MinGW)

# Имя итогового exe
TARGET ?= program
TARGET := $(TARGET).exe

# Каталоги
SRC_DIR := .
BUILD_DIR := build

# Текущая директория проекта
PROJECT_DIR := $(abspath .)

# Флаги компилятора
CFLAGS := -Wall -Wextra -O2 -std=c23 -MMD -MP -I$(PROJECT_DIR)

# ---------------------------
# Рекурсивный поиск всех .c файлов
# ---------------------------

# Находим все поддиректории первого уровня
SUBDIRS := $(wildcard $(SRC_DIR)/*)

# Функция для рекурсивного поиска .c файлов
define find_c_files
$(foreach d,$(SUBDIRS),$(wildcard $(d)/*.c))
endef

# Основной список исходников
CSRCS := $(wildcard $(SRC_DIR)/*.c)
CSRCS += $(call find_c_files)

# ---------------------------
# Генерация списка объектов и зависимостей
# ---------------------------
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(CSRCS))
DEPS := $(OBJS:.o=.d)

# ---------------------------
# Цель сборки exe
# ---------------------------
$(TARGET): $(OBJS)
	@echo Linking $@...
	@gcc $(OBJS) -o $@

# ---------------------------
# Компиляция .c → .o
# ---------------------------
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling $<...
	@gcc $(CFLAGS) -c $< -o $@

# ---------------------------
# Включаем зависимости
# ---------------------------
-include $(DEPS)

# ---------------------------
# Очистка
# ---------------------------
clean:
	@echo Cleaning...
	@rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
