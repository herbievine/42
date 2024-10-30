import { useCallback, useEffect, useRef } from "react";

type UseFileProps = {
  type: "file";
  accept?: string;
  name?: string;
  onSuccess?: (file: File) => void;
};

export function useFile({ type, accept, name, onSuccess }: UseFileProps) {
  const hiddenInputRef = useRef<HTMLInputElement>(null);

  function register() {
    return {
      ref: hiddenInputRef,
      type,
      accept,
      name,
    };
  }

  function open() {
    hiddenInputRef.current?.click();
  }

  const handleOnFileSelect = useCallback(() => {
    const file = hiddenInputRef.current?.files?.[0];

    if (file) {
      onSuccess?.(file);
    }

    hiddenInputRef.current?.removeAttribute("value");
  }, [onSuccess]);

  useEffect(() => {
    const { current } = hiddenInputRef;

    hiddenInputRef.current?.addEventListener("change", handleOnFileSelect);

    return () => {
      current?.removeEventListener("change", handleOnFileSelect);
    };
  }, [handleOnFileSelect]);

  return {
    register,
    open,
    hiddenInputRef,
  };
}
