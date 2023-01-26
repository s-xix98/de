all:
	docker compose up --build

down:
	docker compose down

frontend-it:
	docker exec -it frontend bash

backend-it:
	docker exec -it backend bash

re: down all

.PHONY: all down re frontend-it backend-it
