#See https://aka.ms/containerfastmode to understand how Visual Studio uses this Dockerfile to build your images for faster debugging.

FROM mcr.microsoft.com/dotnet/aspnet:5.0 AS base

RUN apt-get update && apt-get install curl -y
RUN curl -fsSL https://get.docker.com -o get-docker.sh
RUN sh ./get-docker.sh
RUN curl -L "https://github.com/docker/compose/releases/download/1.29.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
RUN chmod +x /usr/local/bin/docker-compose

WORKDIR /app
EXPOSE 80

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["WorkUs/WorkUs.csproj", "WorkUs/"]
COPY ["DataContract/DataContract.csproj", "DataContract/"]
RUN dotnet restore "WorkUs/WorkUs.csproj"
COPY . .
WORKDIR "/src/WorkUs"
RUN dotnet build "WorkUs.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "WorkUs.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "WorkUs.dll"]