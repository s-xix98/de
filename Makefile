HOOKS_DIR := hooks
GIT_HOOKS_DIR := .git/hooks
HOOKS := $(shell find $(HOOKS_DIR) -type f)
GIT_HOOKS := $(HOOKS:$(HOOKS_DIR)%=$(GIT_HOOKS_DIR)%)

all: $(GIT_HOOKS)
	docker compose up --build

down:
	docker compose down

frontend-it:
	docker exec -it frontend bash

backend-it:
	docker exec -it backend bash

re: down all

$(GIT_HOOKS_DIR)/%: $(HOOKS_DIR)/%
	cp $< $@

.PHONY: all down re frontend-it backend-it
