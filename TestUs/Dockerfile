FROM mcr.microsoft.com/dotnet/sdk:5.0 AS base
WORKDIR /app

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["TestUs/TestUs.csproj", "TestUs/"]
COPY ["ConnectionDB/ConnectionDB.csproj", "ConnectionDB/"]
COPY ["DataContract/DataContract.csproj", "DataContract/"]
COPY ["DeployUS/DeployUS.csproj", "DeployUS/"]
COPY ["WorkUs/WorkUs.csproj", "WorkUs/"]

RUN dotnet restore "TestUs/TestUs.csproj"
COPY . .
WORKDIR "/src/TestUs"
RUN dotnet build "TestUs.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "TestUs.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "test","TestUs.dll"]
