FROM node:alpine

WORKDIR /app

ENV PATH /app/node_modules/.bin:$PATH

COPY client/package.json ./

COPY client/package-lock.json ./

RUN npm install --loglevel=error

COPY client/ ./

CMD ["npm", "start"]