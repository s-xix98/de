FROM node:18-slim

USER node

WORKDIR /workdir
RUN chown node:node /workdir

COPY --chown=node:node package*.json ./

RUN npm i

