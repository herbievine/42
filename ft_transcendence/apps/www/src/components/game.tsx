import { useRef, useEffect, useState } from "react";
import { cn } from "../lib/cn";

// TODO: AI create more random movement
// TODO: create Random start direction + start in the opposite of the winner
// TODO: the AIpaddle goes through the walls
// TODO: add keyboard control for the right paddle (real player)
// TODO: win on 10 points
// TODO: stop the AI when the game is paused

type Props = {
  speed: number;
  acceleration: number;
  background: string;
  aiSpeed: number;
  opponent: string;
  onWin: (data: {
    playerScore: number;
    opponentScore: number;
    opponent: "ai" | "local";
  }) => void;
};

const CANVAS_WIDTH = 1000;
const CANVAS_HEIGHT = 700;

export function Game({
  speed,
  acceleration,
  background,
  aiSpeed,
  onWin,
  opponent,
}: Props) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [leftPaddleY, setLeftPaddleY] = useState(100);
  const [rightPaddleY, setRightPaddleY] = useState(100);
  const [pause, setPause] = useState(true);
  const [bufferBallSpeed, setBufferBallSpeed] = useState({
    dx: 2,
    dy: 2,
  });
  const [ball, setBall] = useState({
    x: CANVAS_WIDTH / 2,
    y: CANVAS_HEIGHT / 2,
    dx: 2,
    dy: 2,
  });
  const [aiMoveUp, setAiMoveUp] = useState(true);
  const [aiBallY, setAiBallY] = useState(ball.y);
  const ballRef = useRef(ball);
  const [keyPaddleLeftPressed, setKeyPaddleLeftPressed] = useState({
    up: false,
    down: false,
  });
  const [keyPaddleRightPressed, setKeyPaddleRightPressed] = useState({
    up: false,
    down: false,
  });

  const [scores, setScores] = useState({
    left: 0,
    right: 0,
  });

  const paddleWidth = 10;
  const paddleHeight = 100;
  const ballRadius = 5; //TODO: make it dynamic for vision friendly9
  const paddleSpeed = 4 * (speed / 5 + 1);
  const aiMaxSpeed = 4 * (aiSpeed / 5 + 1);

  const drawRect = (
    ctx: CanvasRenderingContext2D,
    x: number,
    y: number,
    width: number,
    height: number,
    color: string,
  ) => {
    ctx.fillStyle = color;
    ctx.fillRect(x, y, width, height);
  };

  const drawBall = (
    ctx: CanvasRenderingContext2D,
    x: number,
    y: number,
    radius: number,
    color: string,
  ) => {
    ctx.fillStyle = color;
    ctx.beginPath();
    ctx.arc(x, y, radius, 0, Math.PI * 2);
    ctx.fill();
  };

  const keyDownHandler = (e: KeyboardEvent) => {
    if (pause) {
      setKeyPaddleLeftPressed((prev) => ({ ...prev, up: false, down: false }));
      return;
    }
    if (e.key === "w" || e.key === "W")
      setKeyPaddleLeftPressed((prev) => ({ ...prev, up: true }));
    if (e.key === "s" || e.key === "S")
      setKeyPaddleLeftPressed((prev) => ({ ...prev, down: true }));
    if (opponent === "local") {
      if (e.key === "ArrowUp")
        setKeyPaddleRightPressed((prev) => ({ ...prev, up: true }));
      if (e.key === "ArrowDown")
        setKeyPaddleRightPressed((prev) => ({ ...prev, down: true }));
    }
  };

  const keyUpHandler = (e: KeyboardEvent) => {
    if (pause) return;
    if (e.key === "w" || e.key === "W")
      setKeyPaddleLeftPressed((prev) => ({ ...prev, up: false }));
    if (e.key === "s" || e.key === "S")
      setKeyPaddleLeftPressed((prev) => ({ ...prev, down: false }));
    if (opponent === "local") {
      if (e.key === "ArrowUp")
        setKeyPaddleRightPressed((prev) => ({ ...prev, up: false }));
      if (e.key === "ArrowDown")
        setKeyPaddleRightPressed((prev) => ({ ...prev, down: false }));
    }
  };
  const predictBallY = (
    ballX: number,
    ballY: number,
    ballDx: number,
    ballDy: number,
  ) => {
    // predict y position of the ball when it reaches the right wall
    let predictedY = ballY + (ballDy * (CANVAS_WIDTH - ballX)) / ballDx;

    // simulate ball bouncing on top and bottom walls
    while (predictedY < 0 || predictedY > CANVAS_HEIGHT) {
      if (predictedY < 0) predictedY = -predictedY;
      if (predictedY > CANVAS_HEIGHT)
        predictedY = 2 * CANVAS_HEIGHT - predictedY;
    }

    return predictedY;
  };

  const updateBall = () => {
    setBall((prev) => {
      let { x, y, dx, dy } = prev;

      // Ball movement (speed 1-5)
      x += dx * (speed / 5 + 1);
      y += dy * (speed / 5 + 1);

      // Ball collision with top and bottom walls
      if (y - ballRadius < 0 || y + ballRadius > CANVAS_HEIGHT) {
        dy = -dy;
      }

      // Ball collision with paddles
      if (
        (x - ballRadius < paddleWidth + 20 &&
          y > leftPaddleY &&
          y < leftPaddleY + paddleHeight) ||
        (x + ballRadius > CANVAS_WIDTH - paddleWidth - 20 &&
          y > rightPaddleY &&
          y < rightPaddleY + paddleHeight)
      ) {
        dx = -dx;

        dx = Math.sign(dx) * Math.min(Math.abs(dx) + acceleration / 10, 10);
        dy = Math.sign(dy) * Math.min(Math.abs(dy) + acceleration / 10, 10);
      }

      // Ball reset on left or right edge
      // if (x - ballRadius < 0 || x + ballRadius > CANVAS_WIDTH) {
      //   x = CANVAS_WIDTH / 2;
      //   y = CANVAS_HEIGHT / 2;
      //   dx = 2;
      //   dy = 2;
      // }

      const paddleCenterOffset = paddleHeight / 2;

      // AI paddle movement
      if (opponent === "ai") {
        if (rightPaddleY < aiBallY) {
          setRightPaddleY((prev) =>
            Math.min(prev + aiMaxSpeed, aiBallY - paddleCenterOffset),
          );
        } else if (rightPaddleY > aiBallY) {
          setRightPaddleY((prev) =>
            Math.max(prev - aiMaxSpeed, aiBallY - paddleCenterOffset),
          );
        }
      }

      // Ball reset on left or right edge
      if (x - ballRadius < 0) {
        setScores((prev) => ({ ...prev, right: prev.right + 1 }));

        x = CANVAS_WIDTH / 2;
        y = CANVAS_HEIGHT / 2;
        dx = -2;
        dy = Math.random() * 4 - 2;
      } else if (x + ballRadius > CANVAS_WIDTH) {
        setScores((prev) => ({ ...prev, left: prev.left + 1 }));
        x = CANVAS_WIDTH / 2;
        y = CANVAS_HEIGHT / 2;
        dx = 2;
        dy = Math.random() * 4 - 2;
      }

      return { x, y, dx, dy };
    });
  };

  // player paddle movement
  const updatePlayerPaddle = () => {
    if (keyPaddleLeftPressed.up)
      setLeftPaddleY((prev) => Math.max(prev - paddleSpeed, 0));
    if (keyPaddleLeftPressed.down)
      setLeftPaddleY((prev) =>
        Math.min(prev + paddleSpeed, CANVAS_HEIGHT - paddleHeight),
      );
    if (opponent === "local") {
      if (keyPaddleRightPressed.up)
        setRightPaddleY((prev) => Math.max(prev - paddleSpeed, 0));
      if (keyPaddleRightPressed.down)
        setRightPaddleY((prev) =>
          Math.min(prev + paddleSpeed, CANVAS_HEIGHT - paddleHeight),
        );
    }
  };

  // ballRef is used to store the ball state between updates
  useEffect(() => {
    ballRef.current = ball;
  }, [ball]);

  useEffect(() => {
    if (ball.dx !== 0 || ball.dy !== 0)
      setBufferBallSpeed({ dx: ball.dx, dy: ball.dy });
    if (pause) {
      ball.dx = 0;
      ball.dy = 0;
    } else if (!pause) {
      ball.dx = bufferBallSpeed.dx;
      ball.dy = bufferBallSpeed.dy;
    }
  }, [pause]);

  useEffect(() => {
    if (scores.left >= 5 || scores.right >= 5) {
      onWin({
        playerScore: scores.left,
        opponentScore: scores.right,
        opponent: "ai",
      });
      setPause(true);
      setScores({ left: 0, right: 0 });
    }
  }, [scores]);

  // AI paddle movement prediction and update every second
  useEffect(() => {
    const aiUpdateInterval = setInterval(() => {
      const { x, y, dx, dy } = ballRef.current;
      const predictedY = predictBallY(x, y, dx, dy);

      setAiBallY(predictedY);
      setAiMoveUp(Math.random() > 1); // TODO: not working as intended, need to replace by "whenever the moment, sometimes move up, sometimes move down for 0.2sec"
    }, 1000);

    return () => {
      clearInterval(aiUpdateInterval);
    };
  }, []);

  useEffect(() => {
    const canvas = canvasRef.current;
    const ctx = canvas?.getContext("2d");

    const draw = () => {
      if (ctx) {
        ctx.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

        // Draw middle line
        ctx.beginPath();
        ctx.moveTo(CANVAS_WIDTH / 2, 0);
        ctx.lineTo(CANVAS_WIDTH / 2, CANVAS_HEIGHT);
        ctx.stroke();

        // Draw background
        drawRect(ctx, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, background);

        // Draw paddles
        drawRect(ctx, 20, leftPaddleY, paddleWidth, paddleHeight, "#00FF00");
        drawRect(
          ctx,
          CANVAS_WIDTH - paddleWidth - 20,
          rightPaddleY,
          paddleWidth,
          paddleHeight,
          "#FF0000",
        );

        // Draw ball
        drawBall(ctx, ball.x, ball.y, ballRadius, "#0000FF");

        // Draw scores
        ctx.font = "30px Arial";
        ctx.fillText(scores.left.toString(), CANVAS_WIDTH / 2 - 50, 50);
        ctx.fillText(scores.right.toString(), CANVAS_WIDTH / 2 + 25, 50);
      }
    };

    const gameLoop = setInterval(() => {
      updateBall();
      updatePlayerPaddle();
      draw();
    }, 1000 / 60); // 60 FPS

    window.addEventListener("keydown", keyDownHandler);
    window.addEventListener("keyup", keyUpHandler);

    return () => {
      clearInterval(gameLoop);
      window.removeEventListener("keydown", keyDownHandler);
      window.removeEventListener("keyup", keyUpHandler);
    };
  }, [
    leftPaddleY,
    rightPaddleY,
    ball,
    keyPaddleLeftPressed,
    keyPaddleRightPressed,
    pause,
  ]);

  return (
    <div className="relative origin-top-left w-[1000px] h-[700px]">
      <button
        className={cn(
          "absolute w-[1000px] h-[700px] top-0 left-0 bg-black/50 text-white text-3xl",
          pause === false && "hidden -z-10",
        )}
        onClick={() => {
          setPause(false);
          setBall({ x: CANVAS_WIDTH / 2, y: CANVAS_HEIGHT / 2, dx: 2, dy: 2 });
        }}
      >
        Start game
      </button>
      <canvas
        ref={canvasRef}
        width={CANVAS_WIDTH}
        height={CANVAS_HEIGHT}
        style={{ border: "1px solid #000" }}
      />
      <pre>{JSON.stringify(pause, null, 2)}</pre>
    </div>
  );
}
