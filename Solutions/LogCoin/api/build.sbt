ThisBuild / scalaVersion := "2.12.9"
ThisBuild / scalafmtOnCompile := true

scalacOptions ++= Seq("-Ypartial-unification", "-deprecation", "-feature")

val http4sVersion = "0.20.10"

libraryDependencies ++= Seq(
  "org.http4s"     %% "http4s-dsl"          % http4sVersion,
  "org.http4s"     %% "http4s-blaze-server" % http4sVersion,
  "org.http4s"     %% "http4s-blaze-client" % http4sVersion,
  "org.http4s"     %% "http4s-circe"        % http4sVersion,
  "io.circe"       %% "circe-generic"       % "0.11.1",
  "ch.qos.logback" % "logback-classic"      % "1.2.3",
  "org.tpolecat"   %% "doobie-core"         % "0.7.0",
  "org.tpolecat"   %% "doobie-hikari"       % "0.7.0",
  "org.tpolecat"   %% "doobie-postgres"     % "0.7.0",
  "org.tpolecat"   %% "doobie-quill"        % "0.7.0"
)
