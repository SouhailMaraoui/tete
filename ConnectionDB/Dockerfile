FROM mcr.microsoft.com/dotnet/aspnet:5.0 AS base
WORKDIR /app
EXPOSE 80

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["ConnectionDB/ConnectionDB.csproj", "ConnectionDB/"]
COPY ["DataContract/DataContract.csproj", "DataContract/"]
RUN dotnet restore "ConnectionDB/ConnectionDB.csproj"
COPY . .
WORKDIR "/src/ConnectionDB"
RUN dotnet build "ConnectionDB.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "ConnectionDB.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "ConnectionDB.dll"]
